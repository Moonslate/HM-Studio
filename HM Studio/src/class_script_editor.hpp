#pragma once

#include <vector>
#include <string>

#include <wx/filename.h>

#include "class_rom.hpp"
#include "class_script.hpp"
#include "class_file.hpp"
#include "class_finder.hpp"
#include "namespace_math.hpp"

struct RomInfo
{
	uint32_t StartPointers;
	uint32_t ScriptCount;

	uint32_t StartScript;
	uint32_t BlockLenght;
};

enum class ScriptFlags
{
	ERROR_OUTOFRANGE,
	ERROR_NOTEXT,
	SUCCESS,
	INSERT_LESS,
	INSERT_VERIFY,
	INSERT_LARGER,
	INSERT_FIND,
	INSERT_NONE
};

class ScriptEditor
{
public:
	ScriptEditor(Rom& original, Rom& translated);

	~ScriptEditor() = default;
public:
	static std::string FormatPath(size_t number, const std::string& format);
	static std::string PathFormat(const Rom& rom);
	static std::string NameFormat(const Rom& rom);

	std::string GetPath(bool translated);
	std::string GetPath(size_t number, bool translated);
public:
	Rom& GetRom(bool translated);
public:
	uint32_t GetOffset(Rom& rom, size_t number);
	uint32_t GetOffset(Rom& rom);
	uint32_t* GetOffsets(Rom& rom);
	void SetOffset(uint32_t offset);
	void SetOffsets(uint32_t* offets);
	
	inline uint32_t ScriptSize(uint32_t* value);
	inline uint32_t ScriptSize(const uint32_t& offset, Rom& rom);
	uint32_t ScriptSize(const uint32_t& offset, uint8_t* bytes);

	static RomInfo GetRomInformation(const Rom& rom);

	void Dump(Rom& rom);
	ScriptFlags Insert(Rom& rom, Script& script, uint32_t number);
	void Insert();
private:
	void InsertSmaller(Script& script, uint32_t offset, uint32_t oldSize);
	bool InsertLarger(const Script& script, uint32_t oldOffset, uint32_t oldSize, uint32_t newSize);
	void InsertOnly(const Script& script, uint32_t offset);
	void InsertMove(const Script& script, uint32_t oldOffset, uint32_t oldSize, uint32_t newOffset);
	bool InsertVerify(Script& script, uint32_t offset, uint32_t oldSize);
	bool InsertFind(Script& script, uint32_t oldOffset, uint32_t oldSize, uint32_t newSize);
	void EraseScript(uint32_t offset, uint32_t size);

	inline bool IsInsideBlock(const uint32_t& offset);
	inline bool IsFreeSpace(const uint32_t& offset, const uint32_t& size);
private:
	RomInfo m_Info;
public:
	ScriptFlags OpenScript(size_t scriptNum);
	ScriptFlags CheckAndGoScript(size_t index);
public:
	std::string GetCurOriginal();
	std::string GetCurTranslated();
	size_t GetNumber() { return m_Number; }
	bool IsOpened() { return m_Opened; }
	bool ProxText();
	bool PrevText();
	size_t GetCount() { return m_ScriptOriginal.Count(); }
	bool SaveText(const std::string& text);
	void BackupText(const std::string& text);
	std::string GetBackupText() { return m_TextBackup; }
	void SetText(const std::vector<std::string>& text);
	void ReleaseBackup();
	void SetChanged(bool changed) { m_Changed = changed; }
	void SetSaved(bool saved) { m_Saved = saved; }
	std::vector<std::string>& GetTranlated() { return m_Translated; }
	void SaveScript();
	std::string& operator[](size_t index) { return m_Translated[index]; }
	void SetIndex(size_t index) { m_Index = index; }
	size_t GetIndex() { return m_Index; }
	void ReplaceInAllScripts(const std::string& find, const std::string& replace);

	void UpdateScript();
	Script& GetScript() { return m_ScriptTranslated; }
private:
	Script m_ScriptOriginal;
	Script m_ScriptTranslated;

	std::vector<std::string> m_Original;
	std::vector<std::string> m_Translated;

	size_t m_Index = 0;
	size_t m_Size;
	size_t m_Number;	

	Rom& m_RomOriginal;
	Rom& m_RomTranslated;

	std::string m_TextBackup;
	size_t m_IndexBackup = -1;
	bool m_Changed = false;
	bool m_Saved = false;

	bool m_Opened = false;
};