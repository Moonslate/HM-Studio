#include "class_item_editor.hpp"

ItemInfo::ItemInfo(const std::string& name, uint32_t wpi, uint8_t idIndex, uint8_t descriptionIndex) :
					m_Name(name), m_WPI(wpi), m_IdIndex(idIndex), m_DescriptionIndex(descriptionIndex)
{

}

ItemEditor::ItemEditor(const id& i) : Editor(i, L"Item")
{
	GetItensInfos();
}

std::string ItemEditor::GetName(bool translated) const
{
	std::vector<Item> itens = translated ? m_Translated : m_Original;

	return itens[m_Index].GetName();
}

std::string ItemEditor::GetDescription(bool translated) const
{
	std::vector<Item> itens = translated ? m_Translated : m_Original;

	return itens[m_Index].GetDescription();
}

uint32_t ItemEditor::GetImgAdress(bool translated) const
{
	std::vector<Item> itens = translated ? m_Translated : m_Original;

	return itens[m_Index].GetImgAdress();
}

uint32_t ItemEditor::GetPalAdress(bool translated) const
{
	std::vector<Item> itens = translated ? m_Translated : m_Original;

	return itens[m_Index].GetPalAdress();
}

void ItemEditor::SetName(const std::string& name)
{	
	m_Translated[m_Index].SetName(name);
}

void ItemEditor::SetDescription(const std::string& description)
{
	m_Translated[m_Index].SetDescription(description);
}

void ItemEditor::Save(const std::string& name, const std::string& description)
{
	SetName(name);
	SetDescription(description);
	NextText();
}

void ItemEditor::OpenItens(uint8_t index)
{
	m_Index = 0;
	m_InfoIndex = index;

	GetItens(true);
	GetItens(false);

	m_Count = m_Infos[m_InfoIndex].m_Count;
}

void ItemEditor::GetItens(bool translated)
{
	uint8_t bpi = m_Infos[m_InfoIndex].m_WPI * 4;

	char* textBlock = new char[m_Infos[m_InfoIndex].m_BlockLenght];

	RomFile& rom = translated ? m_RomTranslated : m_RomOriginal;

	rom.Seek(m_Infos[m_InfoIndex].m_StartBlock);
	rom.Read(textBlock, m_Infos[m_InfoIndex].m_BlockLenght);

	uint32_t* dataBlock = new uint32_t[m_Infos[m_InfoIndex].m_Count * bpi];

	rom.Seek(m_Infos[m_InfoIndex].m_StartPointers);
	rom.Read(dataBlock, bpi * m_Infos[m_InfoIndex].m_Count);

	const Moon::Hacking::Table& table = rom.GetTable();
	table.Input((uint8_t*)textBlock, m_Infos[m_InfoIndex].m_BlockLenght);

	int32_t addr = 0;

	if (m_RomOriginal.Console == console::DS)
	{
		addr = m_Infos[m_Index].m_StartPointers - 4;
	}

	if (m_RomOriginal.Console == console::GBA)
	{
		addr = 0xF8000000;
	}

	std::vector<Item>& itens = translated ? m_Translated : m_Original;
	itens.resize(m_Infos[m_InfoIndex].m_Count);

	for (size_t i = 0; i < m_Infos[m_InfoIndex].m_Count; ++i)
	{
		uint32_t* curData = dataBlock + (i * m_Infos[m_InfoIndex].m_WPI);

		if (m_RomOriginal.Console == console::GBA)
		{
			uint32_t nameOffset = curData[0] + addr;

			if (IsInsideBlock(nameOffset))
			{
				itens[i].SetName(std::string_view(textBlock + (nameOffset - m_Infos[m_InfoIndex].m_StartBlock)));
			}
			else
			{
				rom.Seek(nameOffset);
				std::string name = rom.ReadString();
				table.Input(name);
				itens[i].SetName(name);
			}

			uint16_t id = *(uint16_t*)(curData + m_Infos[m_InfoIndex].m_IdIndex);

			uint32_t offset3 = (rom.ReadUInt16((rom.ReadUInt16(((id << 2) + m_Adresses[0]) + 2) << 2) + m_Adresses[1]) << 4) + m_Adresses[2]; //It's crazy, isn't? There are more!
			uint32_t image = (rom.ReadUInt16(offset3 + 6) << 5) + m_Adresses[3]; //O.o There is more yet!
			uint32_t palette = (rom.ReadUInt16(offset3 + 0x0a) << 5) + m_Adresses[4]; //Phew...

			itens[i].SetImgAdress(image);
			itens[i].SetPalAdress(palette);			
		}

		uint32_t descriptionOffset = curData[m_Infos[m_InfoIndex].m_DescriptionIndex] + addr;

		if (IsInsideBlock(descriptionOffset))
		{
			itens[i].SetDescription(std::string_view((textBlock + (descriptionOffset - m_Infos[m_InfoIndex].m_StartBlock))));
		}
		else
		{
			rom.Seek(descriptionOffset);
			std::string description = rom.ReadString();
			table.Input(description);
			itens[i].SetDescription(description);
		}		
	}

	delete[] textBlock;
	delete[] dataBlock;
}

void ItemEditor::Dump()
{
	uint32_t size = 0;

	for (const Item& item : m_Translated)
	{
		if (m_RomOriginal.Console == console::GBA)
			size += item.GetName().size() + 1;

		size += item.GetDescription().size() + 1;
	}

	char* block = new char[size];

	char* cur = block;

	for (const Item& item : m_Translated)
	{
		memcpy(cur, item.GetName().c_str(), item.GetName().size() + 1);
		cur += item.GetName().size() + 1;
		memcpy(cur, item.GetDescription().c_str(), item.GetDescription().size() + 1);
		cur += item.GetDescription().size() + 1;
	}

	wxFileName itemDir;
	itemDir.SetPath(m_RomTranslated.m_HomeDir);
	itemDir.AppendDir(L"Itens");

	if(!itemDir.DirExists())
	{
		itemDir.Mkdir(511, wxPATH_MKDIR_FULL);
	}

	itemDir.SetName(m_Infos[m_InfoIndex].m_Name);
	itemDir.SetExt("itens");	

	Moon::File::WriteAllBytes(itemDir.GetFullPath().ToStdString(), block, size);

	delete[] block;
}

void ItemEditor::DumpImages()
{
	uint32_t size = m_Infos[m_InfoIndex].m_Count*((16*16)/2) + ((16*2)* m_Infos[m_InfoIndex].m_Count);

	char* data = new char[size];
	char* cur = data;

	for (const Item& item : m_Translated)
	{
		m_RomTranslated.Seek(item.GetImgAdress());
		m_RomTranslated.Read(cur, (16 * 16) / 2);
		cur += (16 * 16) / 2;
		m_RomTranslated.Seek(item.GetPalAdress());
		m_RomTranslated.Read(cur, 16 * 2);
		cur += 16 * 2;
	}

	wxFileName fn;
	fn.SetPath(m_RomTranslated.m_HomeDir);
	fn.AppendDir(L"Itens");

	if(!fn.DirExists())
	{
		fn.Mkdir(511, wxPATH_MKDIR_FULL);
	}


	fn.SetName(m_Infos[m_InfoIndex].m_Name);
	fn.SetExt("itensimg");	

	Moon::File::WriteAllBytes(fn.GetFullPath().ToStdString(), data, size);

	delete[] data;
}

void ItemEditor::InsertItens()
{
	uint8_t bpi = m_Infos[m_InfoIndex].m_WPI * 4;

	char* textBlock = new char[m_Infos[m_InfoIndex].m_BlockLenght];
	uint32_t* dataBlock = new uint32_t[m_Infos[m_InfoIndex].m_Count * bpi];
	uint32_t offset = 0;

	m_RomTranslated.Seek(m_Infos[m_InfoIndex].m_StartPointers);
	m_RomTranslated.Read(dataBlock, bpi * m_Infos[m_InfoIndex].m_Count);
		
	uint32_t add = m_RomOriginal.Console == console::GBA ? (0x08000000 + m_Infos[m_InfoIndex].m_StartBlock) : m_Infos[m_Index].m_StartPointers - 4;

	for (size_t i = 0; i < m_Infos[m_InfoIndex].m_Count; ++i)
	{		
		uint32_t* curData = dataBlock + (i * m_Infos[m_InfoIndex].m_WPI);

		if (m_RomOriginal.Console == console::GBA)
		{
			const std::string& name = m_Translated[i].GetName();
			memcpy(textBlock + offset, name.c_str(), name.size() + 1);

			curData[0] = (offset + add);
			offset += name.size() + 1;

			if (offset >= m_Infos[m_InfoIndex].m_BlockLenght) return;
		}

		const std::string& description = m_Translated[i].GetDescription();
		memcpy(textBlock + offset, description.c_str(), description.size() + 1);

		curData[m_Infos[m_InfoIndex].m_DescriptionIndex] = (offset + add);
		offset += description.size() + 1;

		if (offset >= m_Infos[m_InfoIndex].m_BlockLenght) return;
	}

	m_RomTranslated.GetTable().Output((unsigned char*)textBlock, m_Infos[m_InfoIndex].m_BlockLenght);

	m_RomTranslated.Seek(m_Infos[m_InfoIndex].m_StartBlock);
	m_RomTranslated.Write(textBlock, m_Infos[m_InfoIndex].m_BlockLenght);

	m_RomTranslated.Seek(m_Infos[m_InfoIndex].m_StartPointers);
	m_RomTranslated.Write(dataBlock, bpi * m_Infos[m_InfoIndex].m_Count);

	m_RomTranslated.Flush();
}

bool ItemEditor::GetTextFromPath(const std::string& path)
{
	std::string file = Moon::File::ReadAllText(path);

	size_t offset = 0;

	for (size_t i = 0; i < m_Count; ++i)
	{
		std::string_view name = file.c_str() + offset;
		offset += name.size() + 1;
		std::string_view description = file.c_str() + offset;
		offset += description.size() + 1;

		m_Translated[i].SetName(name);
		m_Translated[i].SetDescription(description);
	}

	return false;
}

bool ItemEditor::IsInsideBlock(uint32_t offset)
{
	return offset >= m_Infos[m_InfoIndex].m_StartBlock && offset < (m_Infos[m_InfoIndex].m_StartBlock + m_Infos[m_InfoIndex].m_BlockLenght);
}

void ItemEditor::GetItensInfos()
{
	if (m_RomOriginal.Console == console::GBA)
	{
		m_Infos.push_back(ItemInfo("Tools",  3, 1, 2));
		m_Infos.push_back(ItemInfo("Fridge", 4, 2, 3));
		m_Infos.push_back(ItemInfo("Shelf",  3, 1, 2));

		if (m_RomOriginal.Id == id::MFoMT)
		{
			m_Infos[0].m_StartPointers = 0xF305c;
			m_Infos[0].m_Count = 0x51;			
			m_Infos[0].m_StartBlock = 0xF1BB4;
			m_Infos[0].m_BlockLenght = 0x149E;

			m_Infos[1].m_StartPointers = 0xF6228;
			m_Infos[1].m_Count = 0xAB;
			m_Infos[1].m_StartBlock = 0xF3428;
			m_Infos[1].m_BlockLenght = 0x2DFC;

			m_Infos[2].m_StartPointers = 0xF8648;
			m_Infos[2].m_Count = 0x6A;			
			m_Infos[2].m_StartBlock = 0xF6CD8;
			m_Infos[2].m_BlockLenght = 0x196C;

			m_Adresses[0] = 0x607de0;
			m_Adresses[1] = 0x61a2f0;
			m_Adresses[2] = 0x6085c4;
			m_Adresses[3] = 0x60A8E4;
			m_Adresses[4] = 0x617768;
		}

		else if (m_RomOriginal.Id == id::FoMT)
		{
			m_Infos[0].m_StartPointers = 0xEAB0C;
			m_Infos[0].m_Count = 0x51;
			m_Infos[0].m_StartBlock = 0xE9668;
			m_Infos[0].m_BlockLenght = 0x14A0;

			m_Infos[1].m_StartPointers = 0xEDCD8;
			m_Infos[1].m_Count = 0xAB;
			m_Infos[1].m_StartBlock = 0xEAED8;
			m_Infos[1].m_BlockLenght = 0x2DFC;

			m_Infos[2].m_StartPointers = 0xEFED4;
			m_Infos[2].m_Count = 0x5F;
			m_Infos[2].m_StartBlock = 0xEE788;
			m_Infos[2].m_BlockLenght = 0x1748;

			m_Adresses[0] = 0x6678a4;
			m_Adresses[1] = 0x679898;
			m_Adresses[2] = 0x66805c;
			m_Adresses[3] = 0x66a2cc;
			m_Adresses[4] = 0x676dd0;
		}
	} 
	else if (m_RomOriginal.Console == console::DS)
	{
		m_Infos.push_back(ItemInfo("Every", 1, 0, 0));

		if (m_RomOriginal.Id == id::DS)
		{
			m_Infos[0].m_StartPointers = 0x116D204;
			m_Infos[0].m_Count = 0x1bc;
			m_Infos[0].m_StartBlock = 0x116D8F4;
			m_Infos[0].m_BlockLenght = 0x5E64;
		}
	}
}