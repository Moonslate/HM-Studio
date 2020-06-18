#include "class_stc.hpp"

static uint8_t* error_rgb = new uint8_t[768]{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x87, 0x2d, 0x2d, 0xdc, 0x49, 0x49, 0xee, 0x50, 0x50, 0xee, 0x50, 0x50, 0xee, 0x50, 0x50, 0xee, 0x50, 0x50, 0xdd, 0x4b, 0x4b, 0x8c, 0x2d, 0x2d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4c, 0x19, 0x19, 0xda, 0x48, 0x48, 0xea, 0x4f, 0x4f, 0xec, 0x4e, 0x4e, 0xec, 0x4f, 0x4f, 0xed, 0x50, 0x50, 0xed, 0x50, 0x50, 0xec, 0x4f, 0x4f, 0xec, 0x4e, 0x4e, 0xea, 0x4f, 0x4f, 0xdc, 0x48, 0x48, 0x4c, 0x19, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4c, 0x19, 0x19, 0xe4, 0x4b, 0x4b, 0xea, 0x4e, 0x4e, 0xeb, 0x4f, 0x4f, 0xec, 0x4f, 0x4f, 0xed, 0x4f, 0x4f, 0xec, 0x4e, 0x4e, 0xec, 0x4e, 0x4e, 0xed, 0x4f, 0x4f, 0xec, 0x4f, 0x4f, 0xeb, 0x4f, 0x4f, 0xea, 0x4e, 0x4e, 0xe5, 0x4c, 0x4c, 0x4c, 0x19, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd7, 0x45, 0x45, 0xe8, 0x4c, 0x4c, 0xea, 0x4f, 0x4f, 0xf1, 0x99, 0x99, 0xf1, 0x98, 0x98, 0xeb, 0x4f, 0x4f, 0xeb, 0x4d, 0x4d, 0xeb, 0x4d, 0x4d, 0xeb, 0x51, 0x51, 0xf2, 0xa1, 0xa1, 0xf0, 0x8d, 0x8d, 0xea, 0x4e, 0x4e, 0xe8, 0x4c, 0x4c, 0xda, 0x46, 0x46, 0x00, 0x00, 0x00, 0x82, 0x28, 0x28, 0xe6, 0x4b, 0x4b, 0xe8, 0x4c, 0x4c, 0xf0, 0x98, 0x98, 0xf9, 0xf6, 0xf6, 0xf9, 0xf7, 0xf7, 0xf2, 0xa8, 0xa8, 0xea, 0x4e, 0x4e, 0xea, 0x50, 0x50, 0xf3, 0xb8, 0xb8, 0xf9, 0xf7, 0xf7, 0xf8, 0xf5, 0xf5, 0xee, 0x87, 0x87, 0xe8, 0x4c, 0x4c, 0xe6, 0x4b, 0x4b, 0x87, 0x2d, 0x2d, 0xd2, 0x42, 0x42, 0xe6, 0x48, 0x48, 0xe7, 0x4a, 0x4a, 0xe9, 0x92, 0x92, 0xf8, 0xf6, 0xf6, 0xf9, 0xf8, 0xf8, 0xf9, 0xf7, 0xf7, 0xf2, 0xa9, 0xa9, 0xf3, 0xb8, 0xb8, 0xf9, 0xf8, 0xf8, 0xf9, 0xf8, 0xf8, 0xf7, 0xf4, 0xf4, 0xe8, 0x83, 0x83, 0xe7, 0x4a, 0x4a, 0xe6, 0x48, 0x48, 0xd7, 0x44, 0x44, 0xe6, 0x47, 0x47, 0xe5, 0x47, 0x47, 0xe6, 0x48, 0x48, 0xe6, 0x4a, 0x4a, 0xe7, 0x9f, 0x9f, 0xf8, 0xf6, 0xf6, 0xf9, 0xf8, 0xf8, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0xf8, 0xf8, 0xf7, 0xf5, 0xf5, 0xe5, 0x90, 0x90, 0xe7, 0x49, 0x49, 0xe6, 0x48, 0x48, 0xe5, 0x47, 0x47, 0xe6, 0x47, 0x47, 0xe5, 0x45, 0x45, 0xe4, 0x46, 0x46, 0xe5, 0x46, 0x46, 0xe5, 0x47, 0x47, 0xe5, 0x49, 0x49, 0xe7, 0xa2, 0xa2, 0xf9, 0xf9, 0xf9, 0xfa, 0xfa, 0xfa, 0xf9, 0xf9, 0xf9, 0xf8, 0xf7, 0xf7, 0xe5, 0x90, 0x90, 0xe5, 0x49, 0x49, 0xe5, 0x47, 0x47, 0xe5, 0x46, 0x46, 0xe4, 0x46, 0x46, 0xe5, 0x45, 0x45, 0xe3, 0x45, 0x45, 0xe2, 0x45, 0x45, 0xe3, 0x45, 0x45, 0xe4, 0x45, 0x45, 0xe4, 0x4a, 0x4a, 0xf1, 0xb6, 0xb6, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0xf8, 0xf8, 0xef, 0xa6, 0xa6, 0xe4, 0x47, 0x47, 0xe4, 0x45, 0x45, 0xe3, 0x45, 0x45, 0xe2, 0x45, 0x45, 0xe3, 0x45, 0x45, 0xe0, 0x47, 0x47, 0xe0, 0x44, 0x44, 0xe2, 0x44, 0x44, 0xe2, 0x47, 0x47, 0xf0, 0xb5, 0xb5, 0xf9, 0xf8, 0xf8, 0xf9, 0xf8, 0xf8, 0xf7, 0xf6, 0xf6, 0xf8, 0xf7, 0xf7, 0xf9, 0xf8, 0xf8, 0xf9, 0xf7, 0xf7, 0xee, 0xa4, 0xa4, 0xe2, 0x46, 0x46, 0xe2, 0x44, 0x44, 0xe0, 0x44, 0x44, 0xe0, 0x47, 0x47, 0xc8, 0x44, 0x44, 0xdf, 0x40, 0x40, 0xe0, 0x43, 0x43, 0xec, 0x9c, 0x9c, 0xf9, 0xf7, 0xf7, 0xf9, 0xf8, 0xf8, 0xf7, 0xf5, 0xf5, 0xe2, 0x8d, 0x8d, 0xe4, 0x9e, 0x9e, 0xf8, 0xf6, 0xf6, 0xf9, 0xf8, 0xf8, 0xf9, 0xf6, 0xf6, 0xe9, 0x8a, 0x8a, 0xe0, 0x42, 0x42, 0xdf, 0x40, 0x40, 0xce, 0x47, 0x47, 0x78, 0x2d, 0x2d, 0xdc, 0x41, 0x41, 0xdd, 0x41, 0x41, 0xe2, 0x82, 0x82, 0xf7, 0xf3, 0xf3, 0xf7, 0xf4, 0xf4, 0xe1, 0x8b, 0x8b, 0xdf, 0x42, 0x42, 0xdf, 0x42, 0x42, 0xe3, 0x9c, 0x9c, 0xf8, 0xf5, 0xf5, 0xf6, 0xf0, 0xf0, 0xe1, 0x73, 0x73, 0xdd, 0x40, 0x40, 0xdc, 0x41, 0x41, 0x7d, 0x32, 0x32, 0x00, 0x00, 0x00, 0xc7, 0x46, 0x46, 0xdb, 0x3f, 0x3f, 0xdc, 0x41, 0x41, 0xde, 0x7a, 0x7a, 0xde, 0x79, 0x79, 0xdd, 0x40, 0x40, 0xdd, 0x3f, 0x3f, 0xde, 0x3f, 0x3f, 0xdd, 0x41, 0x41, 0xde, 0x82, 0x82, 0xdd, 0x70, 0x70, 0xdd, 0x40, 0x40, 0xdb, 0x3f, 0x3f, 0xca, 0x48, 0x48, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x33, 0x19, 0x19, 0xd3, 0x47, 0x47, 0xd9, 0x3d, 0x3d, 0xda, 0x3d, 0x3d, 0xdb, 0x3d, 0x3d, 0xdc, 0x3d, 0x3d, 0xdc, 0x3d, 0x3d, 0xdc, 0x3d, 0x3d, 0xdc, 0x3d, 0x3d, 0xdb, 0x3d, 0x3d, 0xda, 0x3d, 0x3d, 0xd9, 0x3d, 0x3d, 0xd3, 0x47, 0x47, 0x4c, 0x19, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x33, 0x19, 0x19, 0xc5, 0x46, 0x46, 0xd7, 0x3d, 0x3d, 0xd9, 0x3c, 0x3c, 0xd9, 0x3c, 0x3c, 0xd9, 0x3c, 0x3c, 0xd9, 0x3c, 0x3c, 0xd9, 0x3c, 0x3c, 0xd9, 0x3c, 0x3c, 0xd7, 0x3d, 0x3d, 0xc7, 0x48, 0x48, 0x4c, 0x19, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x73, 0x2d, 0x2d, 0xc1, 0x44, 0x44, 0xd8, 0x46, 0x46, 0xd9, 0x41, 0x41, 0xd9, 0x41, 0x41, 0xd8, 0x46, 0x46, 0xc4, 0x46, 0x46, 0x78, 0x32, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

static uint8_t* error_alpha = new uint8_t[256]{ 0x00, 0x00, 0x00, 0x01, 0x33, 0x99, 0xda, 0xf9, 0xf9, 0xda, 0x99, 0x33, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0a, 0x9b, 0xfb, 0xfd, 0xfe, 0xfe, 0xfe, 0xfe, 0xfd, 0xfb, 0x9b, 0x0a, 0x00, 0x00, 0x00, 0x0a, 0xc1, 0xfd, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfd, 0xc1, 0x0a, 0x00, 0x01, 0x9b, 0xfd, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfd, 0x9b, 0x01, 0x33, 0xfb, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfb, 0x33, 0x99, 0xfd, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfd, 0x99, 0xda, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xda, 0xf9, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xf9, 0xf9, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xf9, 0xda, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xda, 0x99, 0xfd, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfd, 0x99, 0x33, 0xfb, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfb, 0x33, 0x01, 0x9b, 0xfd, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfd, 0x9b, 0x01, 0x00, 0x0a, 0xc1, 0xfd, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfd, 0xc1, 0x0a, 0x00, 0x00, 0x00, 0x0a, 0x9b, 0xfb, 0xfd, 0xfe, 0xfe, 0xfe, 0xfe, 0xfd, 0xfb, 0x9b, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x33, 0x99, 0xda, 0xf9, 0xf9, 0xda, 0x99, 0x33, 0x01, 0x00, 0x00, 0x00 };

wxBitmap STC::m_sIconError(wxImage(16, 16, error_rgb, error_alpha, true));

STC::STC(wxWindow* parent, wxWindowID id) : wxStyledTextCtrl(parent, id)
{
	SetFont(wxFontInfo(10).FaceName("Courier New"));
	CreateGUI();
	DoBinds();

	m_Timer.Start(m_TimeToType);

	if (!SpellChecker::m_sInitialized)
	{
		SpellChecker::Initialize();
	}

	std::string chars = SpellChecker::GetWordChars();

	if (!chars.empty())
	{
		chars.append(1, '-');
		SetWordChars(chars);
	}
}

inline void STC::VerifyLineLenght(size_t line)
{	
	if (m_MaxLineLenght == UINT32_MAX)
		return;

	int lenght = this->GetLineLength(line);	

	if (lenght > m_MaxLineLenght)
	{
		if (!(this->MarkerGet(line) & STC_MARK_ERROR_MASK)) //Verify if the line already has that marker
			this->MarkerAdd(line, STC_MARK_ERROR);
	}
	else if (this->MarkerGet(line) & STC_MARK_ERROR_MASK)
		this->MarkerDelete(line, STC_MARK_ERROR);	
}

inline void STC::VerifyLineLenghtFromPos(size_t from, size_t to)
{		
	size_t fromLine = LineFromPosition(from);
	size_t toLine =   LineFromPosition(to);

	do
	{
		VerifyLineLenght(fromLine);
		++fromLine;
	} while (fromLine <= toLine);
}

inline void STC::VerifyCurLineLenght()
{
	VerifyLineLenght(GetCurrentLine());
}

inline void STC::Highlight(size_t start, size_t lenght, int style)
{	
//
//	The StartStyling(int pos, int mask) is deprecated under wxMSW,
//	but is still in use in wxGTK+ 
//

#ifdef __WXMSW__
	StartStyling(start);
#else ifdef __WXGTK__	
	StartStyling(start, 31);
#endif	
	SetStyling(lenght, style);
}

inline void STC::HighlightAll(const std::vector<size_t>& indexes, size_t lenght, int style)
{
	for (size_t index : indexes)
		Highlight(index, lenght, style);
}

inline void STC::FindAll(size_t start, size_t end, const std::string& s, std::vector<size_t>& result)
{	
	int pos = FindText(start, end, s);
	size_t sSize = s.size();

	if (start > end)
	{
		std::swap(start, end);
	}

	while (pos != -1)
	{
		result.push_back(pos);
		pos = FindText(pos + sSize, end, s);
	}
}

inline void STC::FindAndStyleAllVars(size_t start, size_t end)
{
	for (const std::string& s : m_Vars)
	{
		std::vector<size_t> indexes;
		FindAll(start, end, s, indexes);
		HighlightAll(indexes, s.size(), STC_STYLE_VAR);
	}
}

void STC::SetUserCanAddLine(bool can)
{
	m_UserCanAddLine = can;
}

size_t STC::DeleteLine(size_t ln)
{
	size_t lnStart = PositionFromLine(ln);
	DeleteRange(lnStart, SendMsg(SCI_LINELENGTH, ln, 0));
	return lnStart;
}

size_t STC::CleanLine(size_t ln)
{
	size_t lnStart = DeleteLine(ln);
	InsertText(lnStart, m_Eol);
	return lnStart;
}

void STC::ReplaceLineText(const wxString& line, size_t ln)
{
	size_t lnStart = CleanLine(ln);
	InsertText(lnStart, line);
}

void STC::OnKeyPress(wxKeyEvent& event)
{
	char key = event.GetUnicodeKey();
	int keyCode = event.GetKeyCode();
	bool ctrl = event.GetModifiers() == wxMOD_CONTROL;

	if (ctrl && keyCode != wxKeyCode::WXK_CONTROL)
	{
		size_t pos = m_Keys.find(key, 0);

		if (pos != std::string::npos)
		{
			InsertText(GetCurrentPos(), m_StringsOnKey[pos]);
			GotoPos(GetCurrentPos() + m_StringsOnKey[pos].size());
		}
	}
	else if (!m_UserCanAddLine)
	{
		if (keyCode != wxKeyCode::WXK_RETURN && keyCode != wxKeyCode::WXK_NUMPAD_ENTER)
		{
			return;
		}
	}

	event.Skip();
}

void STC::OnStyleNeeded(wxStyledTextEvent& event)
{	
	if (m_NeedStyle)
	{
		size_t start = PositionFromLine(LineFromPosition(m_TypingStart));
		size_t end = GetLineEndPosition(LineFromPosition(m_TypingEnd));

		Highlight(start, end, STC_STYLE_TEXT);
		FindAndStyleAllVars(start, end);
		VerifyLineLenghtFromPos(start, end);

		m_NeedStyle = false;
	}

	event.Skip();
}

void STC::SpellSTC(size_t start, size_t end)
{
	if (GetTextLength() <= 1) //no needs to spell
		return;

	SetIndicatorCurrent(STC_INDIC_SPELL);	

	start = WordStartPosition(start, true);

	IndicatorClearRange(start, WordEndPosition(end, true) - start);	

	size_t curPosition = start;

	while (curPosition < end)
	{
		size_t wordStart = WordStartPosition(curPosition, true);
		size_t wordEnd = WordEndPosition(curPosition, true);

		size_t wordSize = wordEnd - wordStart;

		curPosition += wordSize + 1;				

		std::string word = GetTextRange(wordStart, wordEnd).ToStdString();

		if (word.size() < 2)
			continue;
		
		if (!SpellChecker::Spell(word))
			IndicatorFillRange(wordStart, wordSize);
	}
}

//-------------------------------------------------------------------------------------//
//Events
//-------------------------------------------------------------------------------------//

void STC::OnModified(wxStyledTextEvent& event)
{			
	size_t textLenght = event.m_length;

	bool deletedAll = false;

	if (event.m_modificationType & wxSTC_MOD_BEFOREDELETE) //user deleted the text
	{
		if (textLenght == GetTextLength()) //and actually all the text
		{
			if (GetLineCount() == 1) //and the STC has one line only
			{
				Refresh(); //solving a bug
				deletedAll = true;
			}
		}
	}

	if (!deletedAll)
	{				
		size_t textPos = event.m_position;		

		if (!m_Typing) //User is not typing
		{
			m_TypingStart = textPos;
			m_TypingEnd = textPos + textLenght;
			m_NeedToSpell = true;			
		}
		else
		{
			if (textPos < m_TypingStart)
				m_TypingStart = textPos;

			if (textPos > m_TypingEnd)
				m_TypingEnd = textPos;
		}

		m_NeedStyle = true;

		m_Timer.Start();
	}

	event.Skip();
}

void STC::OnMouseRight(wxMouseEvent& event)
{
	size_t position = PositionFromPoint(event.GetPosition());
	m_ClickedWordPos.first = WordStartPosition(position, false);
	m_ClickedWordPos.second = WordEndPosition(position, false);
	m_ClickedWord = GetTextRange(m_ClickedWordPos.first, m_ClickedWordPos.second).ToStdString();
	ShowMenu(event.GetPosition());	
}

void STC::InsertOnCtrlKey(const std::string& s, char key)
{
	if (!MathUtil::IsInsideBlock(key, 61, 26))
		return;

	size_t index = m_Keys.find(key, 0);

	if (index != std::string::npos)
	{
		m_StringsOnKey[index] = s;
	}
	else
	{
		m_StringsOnKey.push_back(s);
		m_Keys.push_back((uint16_t)key);
	}
}

void STC::OnTimer(wxTimerEvent& event)
{
	SpellSTC(m_TypingStart, m_TypingEnd);
	m_Typing = false;
}

//Menu
void STC::ShowMenu(wxPoint point)
{
	SuggestToMenu(point);
	
	size_t start = GetSelectionStart();
	size_t end = GetSelectionEnd ();
	
	size_t size = end - start;
		
	m_pMenu->Enable(m_ID_UPPER, size != 0);
	m_pMenu->Enable(m_ID_LOWER, size != 0);
	
	PopupMenu(m_pMenu, point.x, point.y);
}

void STC::SetEOLMode(int eol)
{
	wxStyledTextCtrl::SetEOLMode(eol);

	if (eol == wxSTC_EOL_CRLF)
		m_Eol = "\r\n";
	else if (eol == wxSTC_EOL_CR)
		m_Eol = "\r";
	else if (eol == wxSTC_EOL_LF)
		m_Eol = "\n";
}

wxString STC::GetEOL()
{
	return m_Eol;
}

void STC::SuggestToMenu(wxPoint point)
{
	ClearSuggestions();
	
	if (GetTextLength() >= 2)
	{
		size_t position = PositionFromPoint(point);
		size_t start = WordStartPosition(position, false);
		size_t end = WordEndPosition(position, false);

		if (IndicatorValueAt(STC_INDIC_SPELL, start))
		{
			if (m_ClickedWord.size() >= 2)
			{				
				std::vector<std::string> strings = SpellChecker::Suggest(m_ClickedWord);
				
				m_pMenu->Bind(wxEVT_MENU, &STC::OnAddToTempClick, this, m_pMenu->Append(wxNewId(), wxString("Ignore \"") << m_ClickedWord << "\" For Current Session")->GetId());
				m_pMenu->Bind(wxEVT_MENU, &STC::OnAddToUserClick, this, m_pMenu->Append(wxNewId(), wxString("Add \"") << m_ClickedWord << "\" To Dictionary")->GetId());
				
				for(const std::pair<std::string,size_t> dic : m_ExtraDics)
				{
					m_pMenu->Bind(wxEVT_MENU, &STC::OnAddExtraClick, this, m_pMenu->Append(wxNewId(), wxString("Add \"") << m_ClickedWord << "\" To " << dic.first << " Dictionary")->GetId());
				}
				
				m_pMenu->AppendSeparator();

				if (strings.size() > 0)
				{
					for (size_t i = 0; i < strings.size(); ++i)
					{						
						m_pMenu->Bind(wxEVT_MENU, &STC::OnSuggestionClick, this, m_pMenu->Append(wxNewId(), strings[i])->GetId());
					}
				}
			}
		}
	}
}

void STC::ClearSuggestions()
{
	std::vector<wxMenuItem*> toRemove;
	
	wxMenuItemList& list = m_pMenu->GetMenuItems();

	if (list.size() > m_MenuSize)
	{
		wxMenuItem* item = list[m_MenuSize];

		m_pMenu->Unbind(wxEVT_MENU, &STC::OnAddToTempClick, this, item->GetId());
		m_pMenu->Remove(item);

		item = list[m_MenuSize];
		m_pMenu->Unbind(wxEVT_MENU, &STC::OnAddToUserClick, this, item->GetId());
		m_pMenu->Remove(item);

		item = list[m_MenuSize];
		m_pMenu->Remove(item);

		while (list.size() > m_MenuSize)
		{
			item = list[m_MenuSize];
			m_pMenu->Unbind(wxEVT_MENU, &STC::OnSuggestionClick, this, item->GetId());
			m_pMenu->Remove(item);
		}		
	}
}

void STC::OnSuggestionClick(wxCommandEvent& event)
{	
	int id = event.GetId();
	
	wxMenuItemList& list = m_pMenu->GetMenuItems();

	for (wxMenuItem* item : list)
	{
		if (item->GetId() == id)
		{
			m_ClickedWord.clear();
			DeleteRange(m_ClickedWordPos.first, m_ClickedWordPos.second - m_ClickedWordPos.first);
			GotoPos(m_ClickedWordPos.first);
			AddText(item->GetItemLabelText());
			return;
		}
	}	
	
	event.Skip();	

#ifdef _DEBUG
	_STL_REPORT_ERROR("Menu item not found in the menu.");
#endif	
}

void STC::OnAddToUserClick(wxCommandEvent& event)
{	
	SpellChecker::AddToUser(m_ClickedWord, 0);
	m_ClickedWord.clear();
	SpellSTC(0, GetTextLength());
	
	event.Skip();
}

void STC::OnAddToTempClick(wxCommandEvent& event)
{	
	SpellChecker::AddToTemp(m_ClickedWord);
	m_ClickedWord.clear();
	SpellSTC(0, GetTextLength());
	
	event.Skip();
}

void STC::AppendDicToMenu(const std::string& dicName, size_t index)
{
	m_ExtraDics.push_back(std::pair<std::string, size_t>(dicName, index));
}

void STC::RemoveDicToMenu(size_t index)
{
	for(size_t i = 0; i < m_ExtraDics.size(); ++i)
	{
		m_ExtraDics.erase(m_ExtraDics.begin()+i);
		return;
	}	
	
#ifdef _DEBUG	
	_STL_REPORT_ERROR("Dictionary not fount int the dics list.");
#endif
}

void STC::OnAddExtraClick(wxCommandEvent& event)
{	
	std::string name = m_pMenu->FindItem(event.GetId())->GetItemLabelText().ToStdString();
	name = name.substr(name.find("\" To ") + 5);
	name = name.substr(0, name.find(" "));
	
 	for(const auto& dic : m_ExtraDics)
	{
		if(dic.first == name)
		{		
			SpellChecker::AddToUser(m_ClickedWord, dic.second);
			m_ClickedWord.clear();
			SpellSTC(0, GetTextLength());
			event.Skip();
			return;
		}
	}
	
#ifdef _DEBUG
	_STL_REPORT_ERROR("Dictionary not found in the dics list.");
#endif	
}

void STC::OnUpperLowerCaseClick(wxCommandEvent& event)
{
	if (event.GetId() == m_ID_LOWER)
	{
		LowerCase();
	}
	else
	{
		UpperCase();
	}	
	event.Skip();	
}

void STC::DoBinds()
{
	this->Bind(wxEVT_STC_STYLENEEDED, &STC::OnStyleNeeded, this);
	this->Bind(wxEVT_STC_MODIFIED, &STC::OnModified, this);
	this->Bind(wxEVT_RIGHT_UP, &STC::OnMouseRight, this);
	this->Bind(wxEVT_KEY_DOWN, &STC::OnKeyPress, this);

	m_Timer.Bind(wxEVT_TIMER, &STC::OnTimer, this);
}

void STC::CreateGUI()
{
	this->SetLexer(wxSTC_LEX_CONTAINER);

	this->StyleSetFont(STC_STYLE_TEXT, GetFont());
	this->StyleSetFont(STC_STYLE_VAR, GetFont());
	this->StyleSetFont(STC_STYLE_SIMBOL, GetFont());

	this->StyleSetForeground(STC_STYLE_VAR, wxColour(0, 0, 255));
	this->StyleSetBold(STC_STYLE_VAR, true);
	this->StyleSetForeground(STC_STYLE_SIMBOL, wxColour(0, 128, 0));
	this->StyleSetBold(STC_STYLE_SIMBOL, true);

	this->MarkerDefineBitmap(STC_MARK_ERROR, m_sIconError);

	this->SetMarginWidth(0, 32);
	this->SetMarginType(0, wxSTC_MARGIN_NUMBER);

	this->IndicatorSetStyle(STC_INDIC_FIND, wxSTC_INDIC_ROUNDBOX);
	this->IndicatorSetForeground(STC_INDIC_FIND, wxColour(17, 61, 111));
	this->IndicatorSetUnder(STC_INDIC_FIND, true);
	this->IndicatorSetAlpha(STC_INDIC_FIND, 255);	

	IndicatorSetStyle(STC_INDIC_SPELL, wxSTC_INDIC_SQUIGGLE);
	IndicatorSetForeground(STC_INDIC_SPELL, wxColour(236, 55, 55));
	IndicatorSetUnder(STC_INDIC_SPELL, true);
	IndicatorSetAlpha(STC_INDIC_SPELL, 255);

	SetModEventMask(wxSTC_MOD_INSERTTEXT | wxSTC_MOD_DELETETEXT | wxSTC_MOD_BEFOREDELETE);

	m_pMenu = new wxMenu();
	m_pMenu->Append(wxID_CUT, "Cut");
	m_pMenu->Append(wxID_COPY, "Copy");
	m_pMenu->Append(wxID_PASTE, "Paste");
	m_pMenu->Append(wxID_DELETE, "Delete");
	m_pMenu->Append(wxID_SELECTALL, "Select All");	
	m_pMenu->AppendSeparator();
	
	m_ID_UPPER = m_pMenu->Append(wxNewId(), "UPPERCASE")->GetId();
	m_ID_LOWER = m_pMenu->Append(wxNewId(), "lowercase")->GetId();
	
	m_pMenu->Bind(wxEVT_MENU, &STC::OnUpperLowerCaseClick, this, m_ID_UPPER);
	m_pMenu->Bind(wxEVT_MENU, &STC::OnUpperLowerCaseClick, this, m_ID_LOWER);
	m_pMenu->AppendSeparator();		
		
	m_MenuSize = m_pMenu->GetMenuItems().GetCount();
}
