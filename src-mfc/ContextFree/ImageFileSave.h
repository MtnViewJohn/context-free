#pragma once
#include <afxdlgs.h>
#include <string>

class ImageFileSave : public CFileDialog
{
	DECLARE_DYNAMIC(ImageFileSave)

public:
	ImageFileSave(LPCTSTR name, bool tiled, bool& cropped, int& qual, int& w, int& h);
	virtual ~ImageFileSave();

	bool& m_bCropped;
	int& m_iJpegQuality;
	int& m_iMultWidth;
	int& m_iMultHeight;
protected:
	virtual void OnCheckButtonToggled(DWORD dwIDCtl, BOOL bChecked);
	virtual void OnItemSelected(DWORD dwIDCtl, DWORD dwIDItem);	
	DECLARE_MESSAGE_MAP()
public:
};

