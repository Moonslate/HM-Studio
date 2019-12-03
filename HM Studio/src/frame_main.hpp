#pragma once

#include "wx/wx.h"
#include "wx/treectrl.h"
#include "wx/listctrl.h"

//Frames
#include "frame_script_editor.hpp"
#include "frame_tile_editor_parent.hpp"
#include "frame_item_editor.hpp"

//Static
#include "Studio.h"
#include "class_util_wx_file.hpp"
#include "class_table.hpp"
#include "class_bit_converter.hpp"
#include "class_graphics.hpp"
#include "resource_frame_tile_editor.hpp"
#include "class_log_file.hpp"
//Object
#include "class_script.hpp"
#include "wxUtil/wxRefereceCheckBox.hpp"
#include "OptionWindow.hpp"

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

private:
	DECLARE_EVENT_TABLE();	

	void OnChoiceChanged(wxCommandEvent& event);
	void scriptEditor_onClick(wxCommandEvent& event);
	void OnButtonTileEditor_Click(wxCommandEvent& event);
	void OnButtonTeste1_Click(wxCommandEvent& event);
	void OnButtonDumpOriginal(wxCommandEvent& event);
	void OnButtonDumpTranslated(wxCommandEvent& event);
	void EVT_BUTTON_ItemEditorClick(wxCommandEvent& event);

private:
	uint8_t cur_choice = 0;	
private:
	id GetCurrentId();

//Form
	TileEditorFrame* tileEditorFrame = nullptr;


//UI
private:
	void CreateGUIControls();

	wxBoxSizer* sizer0 = nullptr;
	wxBoxSizer* sizer1 = nullptr;
	wxBoxSizer* sizer2 = nullptr;

	wxStaticBox* romBox = nullptr;
	wxStaticBoxSizer* romSizer = nullptr;
	wxButton* openRom = nullptr;
	wxButton* romBackup = nullptr;

	wxStaticBox* scriptBox = nullptr;
	wxStaticBoxSizer* scriptSizer = nullptr;
	wxButton* dumpTranslated = nullptr;
	wxButton* dumpOriginal = nullptr;
	wxButton* scriptEditor = nullptr;

	wxStaticBox* currentBox = nullptr;
	wxStaticBoxSizer* currentSizer = nullptr;
	wxChoice* currentChoice = nullptr;
	wxCheckBox* currentDefault = nullptr;

	wxButton* graphic_button_tile_editor = nullptr;
	wxStaticBox* graphic_static_box = nullptr;
	wxStaticBoxSizer* graphic_static_sizer = nullptr;
	
	wxButton* save_editor_button = nullptr;
	wxStaticBox* save_editor_box = nullptr;
	wxStaticBoxSizer* save_editor_sizer = nullptr;

	wxButton* teste_button_1 = nullptr;
	wxStaticBox* teste_box = nullptr;
	wxStaticBoxSizer* teste_sizer = nullptr;

	wxButton* m_pGUI_openItemEditor = nullptr;
	wxStaticBox* m_pGUI_boxItemEditor = nullptr;
	wxStaticBoxSizer* m_pGUI_boxSizerItemEditor = nullptr;
	//cScriptEditor* scriptEditor = nullptr;
//id
private:

	enum ID {
		ID_currentChoice = 10001,
		ID_scriptEditor =  10002,
		ID_tileEditor =	   10003,
		ID_saveEditor =	   10004,
		ID_teste1 =		   10005
	};
	

	//wxDECLARE_EVENT_TABLE();
};
