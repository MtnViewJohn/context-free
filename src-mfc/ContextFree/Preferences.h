#pragma once

#include "PrefsPageGeneral.h"
#include "PrefsPageEditor.h"

// Preferences

class Preferences : public CPropertySheet
{
	DECLARE_DYNAMIC(Preferences)

public:
	Preferences();
	virtual ~Preferences();
	bool& m_bFontChanged;

protected:
	PrefsPageGeneral m_wndGeneralPage;
	PrefsPageEditor m_wndEditorPage;
	DECLARE_MESSAGE_MAP()
public:
};


