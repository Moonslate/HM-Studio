#pragma once
#include "wx/file.h"
#include "wx/filename.h"
#include "wx/stdpaths.h"

#include <vector>

#include "class_util_string.hpp"
#include "class_table.hpp"
#include "class_util_wx_file.hpp"

enum class console {
	GBA,
	DS
};

enum class id {
	FoMT,
	MFoMT,
	DS
};

struct offset {
	
	uint32_t Script_start_pointers = 0;
	uint32_t Script_count = 0;	
};

//enum scriptCount {
//	FOMT_SCRIPT_COUNT,
//	MFoMT_SCRIPT_COUNT,
//	HMDS_SCRIPT_COUNT
//};

class Rom : public wxFile
{
public:
	Rom(id i, bool translated);
	~Rom();

	id Id;
	console Console;
	std::string Path;
	std::string Name;
	std::string State;

public:
	std::string GetTablePath();
	void InputTextWithVariables(std::vector<std::string> &original, std::vector<std::string> &translated);
	void OutputTextWithVariables(std::vector<std::string>& translated);

//script
public:
	char scriptName[30] = "Script_%s_%s.%s";

	char scriptExportedName[23] = "Script_Exported_%i.txt";

	std::string GetScriptFullName(int num);
	std::string GetScriptFullPath(int num);
	std::string GetScriptExportedFullPath(int num);

	wxFileName scriptPath;
	wxFileName exportedScriptPath;
	
	void GetOffset(std::vector<uint32_t>& vector);
	void GetOffset(uint32_t& value, int number);
	void GetSize(std::vector<uint32_t>& offsets, std::vector<uint32_t>& output);
	void GetSize(uint32_t offset, uint32_t& output);
	void Dump();

	offset Offset;

//File
public:
	void ReadInt32(uint32_t& value);
	void ReadPointer32(uint32_t& value);
	void ReadBytes(std::vector<uint8_t> &bytes, size_t size);

	void WriteBytes(std::vector<uint8_t> bytes);
	void EraseBlock(size_t size);
	bool VerifyEmptyBlock(size_t size);
	int InsertScript(int number, std::vector<uint8_t>& bytes);
private:
	void SetOffsets();

};
