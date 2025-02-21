#include "pch.h"
#include "ContextFree.h"
#include "ImageFileSave.h"

IMPLEMENT_DYNAMIC(ImageFileSave, CFileDialog)



ImageFileSave::ImageFileSave(LPCTSTR name, bool tiled, bool& cropped, int& qual, int& w, int& h)
	: CFileDialog(FALSE, _T("png"), name, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("PNG files (*.png)|*.png|JPEG files (*.jpg)|*.jpg|SVG files (*.svg)|*.svg||")),
	  m_bCropped(cropped), m_iJpegQuality(qual), m_iMultWidth(w), m_iMultHeight(h)
{
	if (qual < 75 || qual > 100 || qual % 5 != 0)
		qual = 80;
	if (w < 1 || w > 5)
		w = 1;
	if (h < 1 || h > 5)
		h = 1;

	StartVisualGroup(IDC_SIZE_LABEL1, _T("JPEG image quality:"));
	AddComboBox(IDC_JPEGQUALITY);
	AddControlItem(IDC_JPEGQUALITY, ID_FILE_MRU_FILE11, _T("75%"));
	AddControlItem(IDC_JPEGQUALITY, ID_FILE_MRU_FILE12, _T("80%"));
	AddControlItem(IDC_JPEGQUALITY, ID_FILE_MRU_FILE13, _T("85%"));
	AddControlItem(IDC_JPEGQUALITY, ID_FILE_MRU_FILE14, _T("90%"));
	AddControlItem(IDC_JPEGQUALITY, ID_FILE_MRU_FILE15, _T("95%"));
	AddControlItem(IDC_JPEGQUALITY, ID_FILE_MRU_FILE16, _T("100%"));
	SetSelectedControlItem(IDC_JPEGQUALITY, ID_FILE_MRU_FILE11 + (qual - 75) / 5);
	EndVisualGroup();
	if (tiled) {
		AddText(IDC_SIZE_LABEL1, _T(""));
		AddComboBox(IDC_RENDERWIDTH);
		AddControlItem(IDC_RENDERWIDTH, ID_FILE_MRU_FILE1, _T("width x 1"));
		AddControlItem(IDC_RENDERWIDTH, ID_FILE_MRU_FILE2, _T("width x 2"));
		AddControlItem(IDC_RENDERWIDTH, ID_FILE_MRU_FILE3, _T("width x 3"));
		AddControlItem(IDC_RENDERWIDTH, ID_FILE_MRU_FILE4, _T("width x 4"));
		AddControlItem(IDC_RENDERWIDTH, ID_FILE_MRU_FILE5, _T("width x 5"));
		SetSelectedControlItem(IDC_RENDERWIDTH, ID_FILE_MRU_FILE1 + w - 1);
		AddComboBox(IDC_RENDERHEIGHT);
		AddControlItem(IDC_RENDERHEIGHT, ID_FILE_MRU_FILE6, _T("height x 1"));
		AddControlItem(IDC_RENDERHEIGHT, ID_FILE_MRU_FILE7, _T("height x 2"));
		AddControlItem(IDC_RENDERHEIGHT, ID_FILE_MRU_FILE8, _T("height x 3"));
		AddControlItem(IDC_RENDERHEIGHT, ID_FILE_MRU_FILE9, _T("height x 4"));
		AddControlItem(IDC_RENDERHEIGHT, ID_FILE_MRU_FILE10, _T("height x 5"));
		SetSelectedControlItem(IDC_RENDERHEIGHT, ID_FILE_MRU_FILE6 + h - 1);
	} else {
		AddCheckButton(IDC_CROPPED, _T("Crop image"), FALSE);
	}
}

ImageFileSave::~ImageFileSave()
{
}

void ImageFileSave::OnCheckButtonToggled(DWORD dwIDCtl, BOOL bChecked)
{
	if (dwIDCtl == IDC_CROPPED)
		m_bCropped = bChecked;
}

void ImageFileSave::OnItemSelected(DWORD dwIDCtl, DWORD dwIDItem)
{
	if (dwIDCtl == IDC_RENDERWIDTH && dwIDItem >= ID_FILE_MRU_FILE1 && dwIDItem <= ID_FILE_MRU_FILE5)
		m_iMultWidth = dwIDItem - ID_FILE_MRU_FILE1 + 1;
	if (dwIDCtl == IDC_RENDERHEIGHT && dwIDItem >= ID_FILE_MRU_FILE6 && dwIDItem <= ID_FILE_MRU_FILE10)
		m_iMultHeight = dwIDItem - ID_FILE_MRU_FILE6 + 1;
	if (dwIDCtl == IDC_JPEGQUALITY && dwIDItem >= ID_FILE_MRU_FILE11 && dwIDItem <= ID_FILE_MRU_FILE16)
		m_iJpegQuality = (dwIDItem - ID_FILE_MRU_FILE11) * 5 + 75;
}

BEGIN_MESSAGE_MAP(ImageFileSave, CFileDialog)
END_MESSAGE_MAP()

