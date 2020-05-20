#pragma once
#include <vector>

#include <wx/file.h>
#include <wx/filename.h>
#include <wx/stdpaths.h>
#include <wx/utils.h>

#include "class_file.hpp"
#include "class_util_string.hpp"
#include "class_var_table.hpp"
#include "class_script.hpp"
#include "class_stop_watch.hpp"

#include <moon/table.hpp>

#define ROM_BUS 0x8000000
#define ROM_BUS_NOT 0xF7FFFFFF

enum class console {
	GBA,
	DS
};

enum class id {
	FoMT,
	MFoMT,
	DS
};

class RomFile : public wxFile
{
public:
	RomFile(id i, bool translated);
	~RomFile() = default;

	id Id;
	console Console;
	std::string Path;	
	std::string Name;
	std::string State;
	std::string m_EOL;
	std::string m_HomeDir;
	uint8_t m_MaxChars;
	//Table
private:	
	Moon::Hacking::Table m_Table;
	VarTable m_VarTable;

	void SetupVars();
public:
	std::string GetTablePath();
	inline const Moon::Hacking::Table& GetTable() const { return m_Table; }
	inline const VarTable& GetVarTable() const { return m_VarTable; }
	void InputTextWithVariables(std::vector<std::string>& text);
	void OutputTextWithVariables(std::vector<std::string>& text);
	void BackupRom(const std::string& inform);
	inline const std::string& GetEOL() const { return m_EOL; };
	inline const uint8_t GetLineMax() const {return m_MaxChars; }
//File
public:
	//void ReadInt32(uint32_t& value);
	int8_t  ReadInt8();
	int16_t ReadInt16();
	int32_t ReadInt32();

	uint8_t  ReadUInt8();
	uint16_t ReadUInt16();
	uint16_t ReadUInt16(uint32_t off);
	uint32_t ReadUInt32();
	uint64_t ReadUint64(uint32_t off);

	uint32_t ReadPointer32(uint32_t offset);

	std::string ReadString();

	void WriteUInt32(uint32_t number);
	void WriteUInt32(uint32_t number, uint32_t offset);

	void ReadBytes(std::vector<uint8_t> &bytes, size_t size);

	void WriteBytes(std::vector<uint8_t> bytes);
	void WriteBytes(const void* bytes, const size_t size);
};