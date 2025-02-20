#include "pch.h"
#include "ContextFree.h"
#include "ImageFileSave.h"

IMPLEMENT_DYNAMIC(ImageFileSave, CFileDialog)



ImageFileSave::ImageFileSave(LPCTSTR name)
	: CFileDialog(FALSE, _T("png"), name, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("PNG files (*.png)|*.png|JPEG files (*.jpg)|*.jpg|SVG files (*.svg)|*.svg||"))
{
	AddCheckButton(IDC_CROPPED, _T("Crop image"), FALSE);
	StartVisualGroup(IDC_SIZE_LABEL1, _T("JPEG image quality:"));
	AddEditBox(IDC_JPEGQUALITY, _T("80"));
	EndVisualGroup();
}

ImageFileSave::~ImageFileSave()
{
}

void ImageFileSave::OnCheckButtonToggled(DWORD dwIDCtl, BOOL bChecked)
{
	if (dwIDCtl == IDC_CROPPED)
		m_bCropped = bChecked;
}

BOOL ImageFileSave::OnFileNameOK()
{
	CString txt;
	GetEditBoxText(IDC_JPEGQUALITY, txt);
	m_sJpegQuality = (LPCTSTR)txt;
	return 0;
}

BEGIN_MESSAGE_MAP(ImageFileSave, CFileDialog)
END_MESSAGE_MAP()
