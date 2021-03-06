#pragma once

#include <map>

#include <wx/wx.h>
#include <wx/xml/xml.h>
#include <wx/grid.h>
#include <wx/textdlg.h>

#include "class_editor.hpp"
#include "frame_editor.hpp"

#define EDITING_EDITOR_FRAME ValueEditorFrame

enum class ValueType
{
	WordValue,	
	HalfValue,
	ByteValue,
	StringValue,
	CharValue,
	BoolValue
};

enum GridCol
{
	COL_NAME,
	COL_TYPE,
	COL_ADRESS,
	COL_SIZE,
	COL_VALUE
};

class Value
{
public:	
	Value() = default;
	Value(const wxString& name, const ValueType& type = ValueType::WordValue, const uint32_t& offset = 0,  const uint32_t& value = 0)
		: name(name), type(type), offset(offset), value(value) {}
public:
	wxString name;
	ValueType type;
	uint32_t offset;
	uint32_t value;
	wxString str_value;
	bool showOffsetAsHex = true;
	bool showValueAsHex = true;	
public:
	uint32_t GetValueSize() const;
	const wxString& GetValueName() const;
	static ValueType GetValueFromName(const wxString& name);
	void ValueFromString(const wxString& value);
	wxString ValueToString() const;
	wxString OffsetToString() const;	

	bool operator<(const Value& value)
	{
		return offset < value.offset;
	}

};

class ValueEditor : public Editor
{
public:
	ValueEditor(const id& id);
private:	
	wxArrayString m_Files;
	std::vector<Value> m_Values;
	wxString m_File;
public:
	virtual void SaveFile() override;
	virtual void InsertFile() override;
	virtual bool Open(uint32_t index) override;
	bool Open(const wxString& name);
	const wxString& GetName() { return m_File; }
	void AddFile(const wxString& filename);
	wxString GetPath(const wxString& name);	
	void AddValue();
	void AddValue(const Value& value, size_t count = 1);
	void Delete(size_t index);
	const Value& GetValue(size_t index) const { return m_Values[index]; }
	Value& GetValue(size_t index) { return m_Values[index]; }
};

class ValueEditorFrame : public EditorFrame
{
public:
	ValueEditorFrame(const id& id);	
private:
	virtual void UpdateFile() override;
	void UpdateValue(size_t index);
private:
	void OnNewFileClick(wxCommandEvent& event);
	void OnNewValueClick(wxCommandEvent& event);
	void OnNewValue2Click(wxCommandEvent& event);
	void OnDeleteValue(wxCommandEvent& event);
	void OnCellSelected(wxGridEvent& event);
	void OnCellChangeStart(wxGridEditorCreatedEvent& event);
	void OnCellChanging(wxGridEvent& event);
	void OnCellChanged(wxGridEvent& event);
	void OnCellRightClick(wxGridEvent& event);
	void OnToggleHexMenuClick(wxCommandEvent& event);
private:
	ValueEditor* m_pValueEditor = nullptr;
	uint32_t m_OldCount = 0;
	uint32_t m_ColIndex = 0;
	bool m_FirstAutoSize = true;
private:	
	wxGrid* m_pValueList2 = nullptr;
	wxMenu* m_pToggleHexMenu = nullptr;
private:
	void CreateGUIControls();
};