#pragma once
#include <afxdlgs.h>
#include <string>

class RenderParameters;

class MovieFileSave : public CFileDialog
{
	DECLARE_DYNAMIC(MovieFileSave)

public:
	MovieFileSave(std::wstring& temp, LPCTSTR name, BOOL loop, RenderParameters& p);
	virtual ~MovieFileSave();
	PROCESS_INFORMATION processInfo;

protected:
	virtual void OnButtonClicked(DWORD dwIDCtl);
	virtual void OnCheckButtonToggled(DWORD dwIDCtl, BOOL bChecked);
	bool m_bLoop = false;
	std::wstring& m_sTempName;
	RenderParameters& m_sParams;
	DECLARE_MESSAGE_MAP()
public:
};

