#include "frame_main.hpp"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)

EVT_CHOICE(ID_currentChoice, cMain::OnChoiceChanged)
EVT_BUTTON(ID_scriptEditor, cMain::scriptEditor_onClick)
EVT_BUTTON(ID_tileEditor, cMain::OnButtonTileEditor_Click)
EVT_BUTTON(ID_teste1, cMain::OnButtonTeste1_Click)

wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "HM Studio")
{
	CreateGUIControls();
	LogFile::Init(false);
}

cMain::~cMain()
{
}

void cMain::CreateGUIControls()
{	
	this->SetBackgroundColour(wxColour(240, 240, 240, 255));

	sizer0 = new wxBoxSizer(wxHORIZONTAL);
	sizer1 = new wxBoxSizer(wxVERTICAL);

	romBox = new wxStaticBox(this, wxID_ANY, "ROM");
	romSizer = new wxStaticBoxSizer(romBox, wxVERTICAL);

	openRom = new wxButton(this, wxID_ANY, "Open");
	romBackup = new wxButton(this, wxID_ANY, "Backup");

	romSizer->AddSpacer(5);
	romSizer->Add(openRom, 0, wxRIGHT | wxLEFT | wxEXPAND, 5);
	romSizer->AddSpacer(5);
	romSizer->Add(romBackup, 0, wxRIGHT | wxLEFT | wxEXPAND, 5);
	romSizer->AddSpacer(5);

	scriptBox = new wxStaticBox(this, wxID_ANY, "Script");
	scriptSizer = new wxStaticBoxSizer(scriptBox, wxVERTICAL);

	dumpOriginal = new wxButton(this, wxID_ANY, "Dump Original");
	dumpOriginal->Bind(wxEVT_BUTTON, &cMain::OnButtonDumpOriginal, this);
	dumpTranslated = new wxButton(this, wxID_ANY, "Dump Translated");
	dumpTranslated->Bind(wxEVT_BUTTON, &cMain::OnButtonDumpTranslated, this);
	scriptEditor = new wxButton(this, ID_scriptEditor, "Script Editor");

	scriptSizer->AddSpacer(5);
	scriptSizer->Add(dumpOriginal,   0,  wxRIGHT | wxLEFT | wxEXPAND, 5);
	scriptSizer->AddSpacer(5);
	scriptSizer->Add(dumpTranslated, 0, wxRIGHT | wxLEFT		    , 5); //This will be the largest, and the others will expand to match width.
	scriptSizer->AddSpacer(5);
	scriptSizer->Add(scriptEditor,   0, wxRIGHT | wxLEFT | wxEXPAND, 5);
	scriptSizer->AddSpacer(5);	

	save_editor_button = new wxButton(this, ID_saveEditor, "Save Editor");	
	save_editor_box = new wxStaticBox(this, wxID_ANY, "Save");
	save_editor_sizer = new wxStaticBoxSizer(save_editor_box, wxVERTICAL);
	save_editor_sizer->Add(save_editor_button, 0, wxRIGHT | wxLEFT | wxEXPAND, 5);

	graphic_button_tile_editor = new wxButton(this, ID_tileEditor, _("Tile Editor"));
	graphic_static_box = new wxStaticBox(this, wxID_ANY, "Graphic");
	graphic_static_sizer = new wxStaticBoxSizer(graphic_static_box, wxVERTICAL);
	graphic_static_sizer->Add(graphic_button_tile_editor, 0, wxRIGHT | wxLEFT | wxEXPAND, 5);

	currentBox = new wxStaticBox(this, wxID_ANY, "Selected ROM");
	currentSizer = new wxStaticBoxSizer(currentBox, wxVERTICAL);

	currentChoice = new wxChoice(this, ID_currentChoice);
	currentChoice->Insert("FoMT", 0);
	currentChoice->Insert("MFoMT", 1);
	currentChoice->Insert("DS", 2);
	currentChoice->SetSelection(0);
	//currentChoice->Bind(wxEVT_CHOICE, &cMain::OnChoiceChanged, this);
	currentDefault = new wxCheckBox(this, wxID_ANY, "Default");

	currentSizer->AddSpacer(5);
	currentSizer->Add(currentChoice, 0, wxRIGHT | wxLEFT | wxEXPAND, 5);
	currentSizer->AddSpacer(5);
	currentSizer->Add(currentDefault, 0, wxRIGHT | wxLEFT, 5);
	currentSizer->AddSpacer(5);

	sizer1->AddSpacer(5);
	sizer1->Add(romSizer, 0, wxEXPAND, 0);
	sizer1->AddSpacer(5);
	sizer1->Add(scriptSizer); //This will be the largest, and the others will expand to match width.
	sizer1->AddSpacer(5);
	sizer1->Add(save_editor_sizer, 0, wxEXPAND, 0);
	sizer1->AddSpacer(5);
	sizer1->Add(graphic_static_sizer, 0, wxEXPAND, 0);
	sizer1->AddSpacer(5);
	sizer1->Add(currentSizer, 0, wxEXPAND, 0);

	m_pGUI_openItemEditor = new wxButton(this, wxID_ANY, _("Item Editor"));
	m_pGUI_openItemEditor->Bind(wxEVT_BUTTON, &cMain::EVT_BUTTON_ItemEditorClick, this);
	m_pGUI_boxItemEditor = new wxStaticBox(this, wxID_ANY, _("Item"));
	m_pGUI_boxSizerItemEditor = new wxStaticBoxSizer(m_pGUI_boxItemEditor, wxVERTICAL);
	m_pGUI_boxSizerItemEditor->Add(m_pGUI_openItemEditor, 0, 4);

	teste_button_1 = new wxButton(this, ID_teste1, "Teste 1");
	teste_box = new wxStaticBox(this, wxID_ANY, "Teste");

	teste_sizer = new wxStaticBoxSizer(teste_box, wxVERTICAL);	
	teste_sizer->Add(teste_button_1);

	sizer2 = new wxBoxSizer(wxVERTICAL);
	sizer2->AddSpacer(5);
	sizer2->Add(teste_sizer, 0, wxEXPAND, 0);
	sizer2->Add(m_pGUI_boxSizerItemEditor, 0, wxEXPAND, 0);

	sizer0->AddSpacer(5);
	sizer0->Add(sizer1);
	sizer0->AddSpacer(5);
	sizer0->Add(sizer2);
	SetSizer(sizer0);
}

void cMain::OnChoiceChanged(wxCommandEvent& event)
{
	cur_choice = currentChoice->GetSelection();

	event.Skip();
}

void cMain::scriptEditor_onClick(wxCommandEvent& event)
{
	cScriptEditor* formScriptEditor = new cScriptEditor(GetCurrentId());
	formScriptEditor->Show();

	event.Skip();
}

void cMain::OnButtonTileEditor_Click(wxCommandEvent& event)
{
	tileEditorFrame = new TileEditorFrame();
	tileEditorFrame->Show();

	event.Skip();
}

void cMain::OnButtonTeste1_Click(wxCommandEvent& event)
{	
	uint8_t* data = new uint8_t[128] { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
									   0x00, 0x20, 0x00, 0x00, 0x60, 0x76, 0x00, 0x60, 0x56, 0x65,
									   0x00, 0x66, 0x45, 0x54, 0x00, 0x56, 0x54, 0x05, 0x60, 0x45,
									   0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
									   0x01, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x12, 0x00,
									   0x00, 0x00, 0x26, 0x01, 0x00, 0x00, 0x20, 0x01, 0x00, 0x00,
									   0x00, 0x12, 0x00, 0x00, 0x60, 0x54, 0x00, 0x00, 0x50, 0x05,
									   0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
									   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
									   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00,
									   0x00, 0x20, 0x01, 0x00, 0x00, 0x20, 0x01, 0x00, 0x00, 0x00,
									   0x12, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x20, 0x01,
									   0x00, 0x00, 0x20, 0x01, 0x00, 0x00, 0x00, 0x00 };

	uint8_t pal[512] = { 0xe0, 0x03, 0x00, 0x00, 0x1a, 0x2f, 0x1a, 0x2f, 0x1f, 0x00, 0xff, 0x3e, 0x52, 0x4a, 0xd6, 0x5a, 0x39, 0x67, 0x7b, 0x6f,
					  0xbd, 0x77, 0xff, 0x7f, 0xe1, 0x5a, 0x49, 0x67, 0xb1, 0x73, 0xf9, 0x7f, 0xe0, 0x03, 0x29, 0x25, 0x8c, 0x31, 0xdd, 0x7f,
					  0x51, 0x6f, 0x73, 0x73, 0xb4, 0x7b, 0xda, 0x7f, 0xdd, 0x7f, 0x7a, 0x77, 0x16, 0x6b, 0x93, 0x5e, 0x2f, 0x52, 0xae, 0x66,
					  0x6c, 0x5a, 0xcc, 0x45, 0xe0, 0x03, 0x29, 0x25, 0x8c, 0x31, 0xdd, 0x7f, 0x51, 0x6f, 0x73, 0x73, 0xb4, 0x7b, 0xda, 0x7f,
					  0xdd, 0x7f, 0x7a, 0x77, 0x16, 0x6b, 0x93, 0x5e, 0x2f, 0x52, 0xae, 0x66, 0x6c, 0x5a, 0xcc, 0x45, 0xe0, 0x03, 0x7a, 0x02,
					  0x90, 0x01, 0x7c, 0x6f, 0x19, 0x67, 0xb5, 0x56, 0x31, 0x46, 0xae, 0x39, 0x4a, 0x29, 0xfe, 0x4b, 0x7c, 0x6f, 0xb5, 0x56,
					  0xae, 0x39, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x03, 0x7a, 0x02, 0x90, 0x01, 0x7c, 0x6f, 0x19, 0x67, 0xb5, 0x56,
					  0x31, 0x46, 0xae, 0x39, 0x4a, 0x29, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
					  0xe0, 0x03, 0x7a, 0x02, 0x90, 0x01, 0x7c, 0x6f, 0x19, 0x67, 0xb5, 0x56, 0x31, 0x46, 0xae, 0x39, 0x4a, 0x29, 0x00, 0x00,
					  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x03, 0x7a, 0x02, 0x90, 0x01, 0x7c, 0x6f,
					  0x19, 0x67, 0xb5, 0x56, 0x31, 0x46, 0xae, 0x39, 0x4a, 0x29, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
					  0x00, 0x00, 0x00, 0x00, 0xe0, 0x03, 0xf7, 0x2f, 0xb5, 0x1f, 0x6e, 0x0f, 0x0a, 0x0b, 0x84, 0x02, 0x00, 0x00, 0x00, 0x00,
					  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x03, 0xff, 0x7f,
					  0xff, 0x57, 0xff, 0x2b, 0xff, 0x03, 0x7f, 0x03, 0xff, 0x02, 0x59, 0x02, 0x91, 0x09, 0x39, 0x67, 0x10, 0x42, 0x8c, 0x31,
					  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
					  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
					  0x5a, 0x6b, 0x0c, 0x05, 0xe9, 0x08, 0x0d, 0x01, 0x3a, 0x02, 0x7c, 0x06, 0x4f, 0x05, 0x91, 0x05, 0x5a, 0x0e, 0xbe, 0x0e,
					  0x7c, 0x0e, 0xde, 0x16, 0xf8, 0x05, 0xd5, 0x05, 0x66, 0x00, 0x0d, 0x0d, 0xe0, 0x03, 0xca, 0x04, 0x5f, 0x00, 0xff, 0x00,
					  0x5f, 0x01, 0x1f, 0x02, 0xff, 0x7f, 0x5f, 0x02, 0xff, 0x02, 0x3f, 0x07, 0x9f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
					  0x00, 0x00, 0x00, 0x00, 0xe0, 0x03, 0x00, 0x00, 0x1a, 0x2f, 0x1a, 0x2f, 0x1f, 0x00, 0xff, 0x3e, 0x52, 0x4a, 0xd6, 0x5a,
					  0x39, 0x67, 0x7b, 0x6f, 0xbd, 0x77, 0xff, 0x7f, 0xe1, 0x5a, 0x49, 0x67, 0xb1, 0x73, 0xf9, 0x7f, 0xe0, 0x03, 0x00, 0x00,
					  0x1a, 0x2f, 0x1a, 0x2f, 0x1f, 0x00, 0xff, 0x3e, 0x52, 0x4a, 0xd6, 0x5a, 0x39, 0x67, 0x7b, 0x6f, 0xbd, 0x77, 0xff, 0x7f,
					  0xe1, 0x5a, 0x49, 0x67, 0xb1, 0x73, 0xf9, 0x7f, 0xe0, 0x03, 0xcb, 0x08, 0xf3, 0x04, 0xe6, 0x35, 0xb1, 0x21, 0x5b, 0x1d,
					  0xa5, 0x66, 0x36, 0x2a, 0x3f, 0x36, 0x4a, 0x73, 0x3c, 0x63, 0x5f, 0x3b, 0xfd, 0x23, 0xdf, 0x5b, 0xff, 0x77, 0x00, 0x00,
					  0x5a, 0x6b, 0x64, 0x10, 0xe8, 0x20, 0xa6, 0x18, 0x21, 0x04, 0x4a, 0x2d, 0xae, 0x39, 0x11, 0x46, 0x94, 0x52, 0x18, 0x67,
					  0x91, 0x05, 0xf5, 0x11, 0x2e, 0x05, 0xea, 0x08, 0xbd, 0x77, 0xff, 0x7f };


	Graphics* g = new Graphics(data, 4, 16, 16, true);
	g->DecodePalette(pal);
	g->SetPaletteIndex(4);	
	g->ToImage().SaveFile("teste.bmp", wxBitmapType::wxBITMAP_TYPE_BMP);

	event.Skip();
}

void cMain::OnButtonDumpOriginal(wxCommandEvent& event)
{	
	Rom* rom = new Rom(GetCurrentId(), true);
	if (rom->IsOpened())
	rom->Dump();
	else
		wxMessageBox("Cant dump the ROM because it's not opened... Maybe don't exists...", "Huh?", 5L, this);
	delete rom;

	event.Skip();
}

void cMain::OnButtonDumpTranslated(wxCommandEvent& event)
{
	if (wxMessageBox(_("Are you sure? It will erase your scripts if you already made changes..."), "Huh?", wxICON_QUESTION | wxYES_NO, this) == wxID_CANCEL)
	return;

	Rom* rom = new Rom(GetCurrentId(), true);
	if (rom->IsOpened())
		rom->Dump();
	else
		wxMessageBox(_("Cant dump the ROM because it's not opened... Maybe don't exists..."), "Huh?", 5L, this);
	delete rom;

	event.Skip();
}

void cMain::EVT_BUTTON_ItemEditorClick(wxCommandEvent& event)
{
	ItemEditorFrame* itemEditorFrame = new ItemEditorFrame();
	itemEditorFrame->Show();
	GetCurrentId();
	event.Skip();
}

id cMain::GetCurrentId()
{
	switch (cur_choice)
	{
	case (int)id::FoMT:
		return id::FoMT;
		break;
	case (int)id::MFoMT:
		return id::MFoMT;
		break;
	case (int)id::DS:
		return id::DS;
		break;
	default:
		wxMessageBox("This is not suposed to happen...", "Huh?", 5L, this);
		return (id)-1;
		break;
	}
}
