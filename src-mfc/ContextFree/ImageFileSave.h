#pragma once
#include <afxdlgs.h>
#include <string>

class ImageFileSave : public CFileDialog
{
	DECLARE_DYNAMIC(ImageFileSave)

public:
	ImageFileSave(LPCTSTR name);
	virtual ~ImageFileSave();

	bool m_bCropped = false;
	std::wstring m_sJpegQuality;
protected:
	virtual void OnCheckButtonToggled(DWORD dwIDCtl, BOOL bChecked);
	virtual BOOL OnFileNameOK();
	DECLARE_MESSAGE_MAP()
public:
};

