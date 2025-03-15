// GalleryUpload.cpp : implementation file
//

#include "pch.h"
#include "ContextFree.h"
#include "afxdialogex.h"
#include "GalleryUpload.h"
#include "UploadParams.h"
#include "vector"
#include "upload.h"
#include "cfdg.h"
#include "ChildFrm.h"
#include <sstream>
#include "WinSystem.h"
#include "EditLock.h"

namespace {
	std::vector<const wchar_t*> LicenseIndicators{
		L"no change", L"Public Domain: CC Zero", L"CC Attribution",
		L"CC Attribution-ShareAlike", L"CC Attribution-NoDerivatives", L"CC Attribution-NonCommercial", 
		L"CC Attribution-NonCommercial-ShareAlike",
		L"CC Attribution-NonCommercial-NoDerivatives", L"No CC license, full copyright"
	};
	std::vector<const wchar_t*> LicenseNames{
		L"", L"CC0 1.0 Universal (CC0 1.0) Public Domain Dedication",
		L"Creative Commons Attribution 4.0 International", 
		L"Creative Commons Attribution-ShareAlike 4.0 International",
		L"Creative Commons Attribution-NoDerivatives 4.0 International",
		L"Creative Commons Attribution-NonCommercial 4.0 International",
		L"Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International",
		L"Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International",
		L"No CC license, full copyright"
	};
	std::vector<const wchar_t*> LicenseImages{
		L"", L"https://licensebuttons.net/p/zero/1.0/88x31.png",
		L"https://licensebuttons.net/l/by/4.0/88x31.png", 
		L"https://licensebuttons.net/l/by-sa/4.0/88x31.png",
		L"https://licensebuttons.net/l/by-nd/4.0/88x31.png",
		L"https://licensebuttons.net/l/by-nc/4.0/88x31.png",
		L"https://licensebuttons.net/l/by-nc-sa/4.0/88x31.png",
		L"https://licensebuttons.net/l/by-nc-nd/4.0/88x31.png", L""
	};
	std::vector<const wchar_t*> LicenseURLs{
		L"", L"https://creativecommons.org/publicdomain/zero/1.0/",
		L"https://creativecommons.org/licenses/by/4.0/",
		L"https://creativecommons.org/licenses/by-sa/4.0/",
		L"https://creativecommons.org/licenses/by-nd/4.0/",
		L"https://creativecommons.org/licenses/by-nc/4.0/",
		L"https://creativecommons.org/licenses/by-nc-sa/4.0/",
		L"https://creativecommons.org/licenses/by-nc-nd/4.0/", L""
	};
	std::vector<UINT> LicenceIDs{
		0, IDB_CC0, IDB_BY, IDB_BYSA, IDB_BYND, IDB_BYNC, IDB_BYNCSA, IDB_BYNCND, 0
	};

	struct AutoCmpWStr {
		inline bool operator()(const std::wstring& a, const std::wstring& b) const
		{
			return _wcsicmp(a.c_str(), b.c_str()) < 0;        // a POSIX function
		}
		inline int operator()(const std::wstring& a, const std::wstring& b, int len)
		{
			return _wcsnicmp(a.c_str(), b.c_str(), len);
		}
	};
	
	std::vector<std::string> AllTags;
	std::set<std::wstring, AutoCmpWStr> AllTagsL;
}

// GalleryUpload dialog

std::atomic_bool GalleryUpload::TagsLoaded = false;

IMPLEMENT_DYNAMIC(GalleryUpload, CDialogEx)

GalleryUpload::GalleryUpload(CChildFrame& child, UploadParams& params, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_UPLOAD, pParent)
	, m_rChild(child)
	, m_rParams(params)
	, m_sUsername(UploadParams::Username)
	, m_sPassword(UploadParams::Password)
	, m_sTitle(params.cfdgName)
	, m_sNotes(_T(""))
	, m_sFilename(params.cfdgName)
	, m_sVariation(params.variationText)
	, m_iJPEGPNG(m_rChild.m_WinCanvas->colorCount256() ? 1 : 0)
	, m_sCCname(_T(""))
{
	for (int i = 1; i < 8; ++i)
		if (m_rParams.ccLicense == LicenseURLs[i]) {
			m_iCurrentLicense = i;
			break;
		}
	if (m_iCurrentLicense == 0 && m_rParams.ccName == LicenseNames[8])
		m_iCurrentLicense = 8;
	m_sCCname = LicenseNames[m_iCurrentLicense];
	m_iInitialLicense = m_iCurrentLicense;
}

GalleryUpload::~GalleryUpload()
{
}

void GalleryUpload::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_USERNAME, m_sUsername);
	DDX_Text(pDX, IDC_PASSWORD, m_sPassword);
	DDX_Text(pDX, IDC_TITLE, m_sTitle);
	DDX_Text(pDX, IDC_NOTES, m_sNotes);
	DDX_Text(pDX, IDC_FILENAME, m_sFilename);
	DDX_Control(pDX, IDC_WIDTHSPIN, m_ctrlWidthSpin);
	DDX_Control(pDX, IDC_HEIGHTSPIN, m_ctrlHeightSpin);
	DDX_Text(pDX, IDC_VARIATION, m_sVariation);
	DDX_Radio(pDX, IDC_JPEG, m_iJPEGPNG);
	DDX_Control(pDX, IDC_CROP, m_ctrlCropTile);
	DDX_Control(pDX, IDC_LICENSE, m_ctrlLicense);
	DDX_Text(pDX, IDC_CCNAME, m_sCCname);
	DDX_Control(pDX, IDC_CCIMAGE, m_ctrlCCimage);
	DDX_Control(pDX, IDC_MULTSTATIC1, m_ctrlMult1);
	DDX_Control(pDX, IDC_MULTSTATIC2, m_ctrlMult2);
	DDX_Control(pDX, IDC_MULTSTATIC3, m_ctrlMult3);
	DDX_Control(pDX, IDC_WIDTH, m_ctrlMultWidth);
	DDX_Control(pDX, IDC_HEIGHT, m_ctrlMultHeight);
	DDX_Control(pDX, IDC_UPLOAD, m_ctrlUpload);
	DDX_Control(pDX, IDCANCEL, m_ctrlCancel);
	DDX_Control(pDX, IDC_ACCOUNT, m_ctrlAccount);
	DDX_Control(pDX, IDC_TAG, m_ctrlTagEdit);
	DDX_Control(pDX, IDC_TAGLIST, m_ctrlTagsList);
	DDX_Control(pDX, IDC_TAGMOVE, m_ctrlTagMove);
}

using WinSystem::WM_USER_RENDER_COMPLETE;

BEGIN_MESSAGE_MAP(GalleryUpload, CDialogEx)
	ON_BN_CLICKED(IDC_ACCOUNT, &GalleryUpload::OnClickedAccount)
	ON_BN_CLICKED(IDC_CCIMAGE, &GalleryUpload::OnClickedccImage)
	ON_BN_CLICKED(IDC_UPLOAD, &GalleryUpload::OnClickedUpload)
	ON_CBN_SELCHANGE(IDC_LICENSE, &GalleryUpload::OnSelchangeLicense)
	ON_MESSAGE(WM_USER_RENDER_COMPLETE, &GalleryUpload::UploadDone)
	ON_WM_CLOSE()
	ON_CBN_SELCHANGE(IDC_TAGLIST, &GalleryUpload::OnSelchangeTaglist)
	ON_CBN_EDITCHANGE(IDC_TAG, &GalleryUpload::OnEditchangeTag)
	ON_BN_CLICKED(IDC_TAGMOVE, &GalleryUpload::OnClickedTagMove)
END_MESSAGE_MAP()


// GalleryUpload message handlers

BOOL GalleryUpload::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_ctrlWidthSpin.SetRange(1, 5);
	m_ctrlWidthSpin.SetPos(1);
	m_ctrlHeightSpin.SetRange(1, 5);
	m_ctrlHeightSpin.SetPos(1);

	if (m_rParams.Tiled) {
		m_ctrlWidthSpin.EnableWindow(m_rParams.Tiled & 1);
		m_ctrlHeightSpin.EnableWindow(m_rParams.Tiled & 2);
		m_ctrlCropTile.SetWindowTextW(L"Tiled");
		m_ctrlCropTile.SetCheck(BST_CHECKED);
	} else {
		m_ctrlWidthSpin.SetWindowPos(NULL, 0, 0, 0, 0,
			SWP_HIDEWINDOW | SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);
		m_ctrlHeightSpin.SetWindowPos(NULL, 0, 0, 0, 0,
			SWP_HIDEWINDOW | SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);
		m_ctrlMult1.SetWindowPos(NULL, 0, 0, 0, 0,
			SWP_HIDEWINDOW | SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);
		m_ctrlMult2.SetWindowPos(NULL, 0, 0, 0, 0,
			SWP_HIDEWINDOW | SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);
		m_ctrlMult3.SetWindowPos(NULL, 0, 0, 0, 0,
			SWP_HIDEWINDOW | SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);
		m_ctrlMultWidth.SetWindowPos(NULL, 0, 0, 0, 0,
			SWP_HIDEWINDOW | SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);
		m_ctrlMultHeight.SetWindowPos(NULL, 0, 0, 0, 0,
			SWP_HIDEWINDOW | SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);
	}

	for (auto indicator : LicenseIndicators)
		m_ctrlLicense.AddString(indicator);
	m_ctrlLicense.SetCurSel(m_iCurrentLicense);

	m_ctrlCCimage.SetImage(
		LicenceIDs[m_iCurrentLicense], 
		LicenceIDs[m_iCurrentLicense], 
		LicenceIDs[m_iCurrentLicense]);

	m_ctrlCCimage.SetMouseCursorHand();
	m_ctrlAccount.SetMouseCursorHand();
	m_ctrlCancel.m_nFlatStyle = CMFCButton::FlatStyle::BUTTONSTYLE_SEMIFLAT;
	m_ctrlCCimage.m_nFlatStyle = CMFCButton::FlatStyle::BUTTONSTYLE_SEMIFLAT;
	m_ctrlAccount.m_nFlatStyle = CMFCButton::FlatStyle::BUTTONSTYLE_SEMIFLAT;

	if (TagsLoaded)
		InitTagsAC();
	else
		CWinThread* rt = ::AfxBeginThread(TagsControllingFunction, GetSafeHwnd(), 0, 0, 0);
	m_ctrlTagEdit.SetCueBanner(L"Type or select tag");

	m_ctrlTagMove.SetWindowTextW(m_eTagMoveDirection == TagMoveDirection::AddToList ? L"►" : L"◄");

	if (m_ctrlToolTip.Create(this)) {
		m_ctrlToolTip.AddTool(&m_ctrlTagEdit, L"Type or select tag");
		m_ctrlToolTip.AddTool(&m_ctrlTagMove, 
			m_eTagMoveDirection == TagMoveDirection::AddToList  ? L"Add tag to tags list" 
																: L"Remove tag from tags list");
		m_ctrlToolTip.AddTool(&m_ctrlTagsList, L"The list of tags");
		m_ctrlToolTip.AddTool(&m_ctrlCCimage, L"Click to see license details");
	}

	return TRUE;
}

void GalleryUpload::InitTagsAC()
{
	for (auto&& tag : AllTagsL)
		m_ctrlTagEdit.AddString(tag.c_str());
}

void GalleryUpload::OnClickedAccount()
{
	ShellExecute(NULL, L"open", L"https://www.contextfreeart.org/phpbb/ucp.php?mode=register", NULL, NULL, SW_SHOWNORMAL);
}

void GalleryUpload::OnClickedccImage()
{
	if (*LicenseURLs[m_iCurrentLicense])
		ShellExecute(NULL, L"open", LicenseURLs[m_iCurrentLicense], NULL, NULL, SW_SHOWNORMAL);
}

void GalleryUpload::OnSelchangeLicense()
{
	UpdateData();
	int newLicense = m_ctrlLicense.GetCurSel();
	m_iCurrentLicense = newLicense ? newLicense : m_iInitialLicense;
	UINT newLicenseID = LicenceIDs[m_iCurrentLicense];
	m_ctrlCCimage.SetImage(newLicenseID, newLicenseID, newLicenseID);
	m_ctrlCCimage.Invalidate();
	m_sCCname = LicenseNames[m_iCurrentLicense];
	UpdateData(FALSE);
}

void GalleryUpload::OnClickedUpload()
{
	if (m_iDesignID) {
		OnOK();
		return;
	}

	Upload upload;
	UpdateData();

	UploadParams::Modify(m_rParams.Username, m_sUsername);
	UploadParams::Modify(m_rParams.Password, m_sPassword);
	if (m_iCurrentLicense) {
		UploadParams::Modify(m_rParams.ccLicense, LicenseURLs[m_iCurrentLicense]);
		UploadParams::Modify(m_rParams.ccName, LicenseNames[m_iCurrentLicense]);
		UploadParams::Modify(m_rParams.ccImage, LicenseImages[m_iCurrentLicense]);
	}
	if (UploadParams::Modified)
		UploadParams::Save();

	upload.mUserName = Utf16ToUtf8((LPCTSTR)m_sUsername);
	upload.mPassword = Utf16ToUtf8((LPCTSTR)m_sPassword);
	upload.mTitle = Utf16ToUtf8((LPCTSTR)m_sTitle);
	upload.mNotes = Utf16ToUtf8((LPCTSTR)m_sNotes);

	for (int i = 0; i < m_ctrlTagsList.GetCount(); ++i) {
		CString tag;
		m_ctrlTagsList.GetLBText(i, tag);
		if (AllTagsL.insert((LPCTSTR)tag).second)		// Save new tags for future uploads
			m_ctrlTagEdit.AddString(tag);
		if (!upload.mTags.empty())
			upload.mTags.push_back(' ');
		upload.mTags.append(Utf16ToUtf8(tag));
	}

	upload.mFileName = Utf16ToUtf8((LPCTSTR)m_sFilename) + ".cfdg";
	upload.mVariation = m_rParams.variation;
	upload.mTiled = m_rParams.Tiled && m_ctrlCropTile.GetCheck() == BST_CHECKED ? m_rParams.Tiled : 0;
	upload.mCompression = m_iJPEGPNG == 0 ? Upload::CompressJPEG : Upload::CompressPNG8;
	upload.mccLicenseURI = Utf16ToUtf8((LPCTSTR)m_rParams.ccLicense);
	upload.mccLicenseName = Utf16ToUtf8((LPCTSTR)m_rParams.ccName);
	upload.mccLicenseImage = Utf16ToUtf8((LPCTSTR)m_rParams.ccImage);
	upload.mText = m_rParams.cfdgText.c_str();
	upload.mTextLen = m_rParams.cfdgText.length();

	bool crop = m_rParams.Tiled || m_ctrlCropTile.GetCheck() == BST_CHECKED;

	IStream* spStream = nullptr;
	HRESULT hr = ::CreateStreamOnHGlobal(NULL, TRUE, &spStream);
	if (!SUCCEEDED(hr)) {
		::MessageBeep(MB_ICONASTERISK);
		TRACE1("Couldn't create stream: %x\n", hr);
		return;
	}

	auto stat = m_rChild.SaveJPEG(spStream, nullptr, crop, m_ctrlWidthSpin.GetPos(),
		m_ctrlHeightSpin.GetPos(), m_iJPEGPNG == 0 ? 90 : 0);
	if (stat != S_OK) {
		::MessageBeep(MB_ICONASTERISK);
		TRACE1("Image save failed: %d\n", stat);
		return;
	}

	HGLOBAL hMem = NULL;
	hr = ::GetHGlobalFromStream(spStream, &hMem);
	if (!SUCCEEDED(hr)) {
		::MessageBeep(MB_ICONASTERISK);
		TRACE1("Couldn't get image data: %x\n", hr);
		return;
	}

	if (!(upload.mImageLen = ::GlobalSize(hMem)) || !(upload.mImage = (const char*)::GlobalLock(hMem))) {
		::MessageBeep(MB_ICONASTERISK);
		TRACE1("Couldn't access image data: %d\n", GetLastError());
		return;
	}

	std::ostringstream design;
	upload.generatePayload(design);

	::GlobalUnlock(hMem);
	spStream->Release();

	m_sPayload = design.str();

	CWinThread* rt = ::AfxBeginThread(UploadControllingFunction, this, 0, 0, CREATE_SUSPENDED);
	BOOL good =
		::DuplicateHandle(::GetCurrentProcess(),
			rt->m_hThread,
			::GetCurrentProcess(),
			&m_hRenderThread,
			DUPLICATE_SAME_ACCESS,
			FALSE,
			0);
	::ResumeThread(m_hRenderThread);

	m_ctrlUpload.SetWindowTextW(L"Uploading");
	m_ctrlUpload.EnableWindow(FALSE);
}

UINT GalleryUpload::UploadControllingFunction(LPVOID pParam)
{
	GalleryUpload* cf = reinterpret_cast<GalleryUpload*>(pParam);
	if (cf == NULL || !cf->IsKindOf(RUNTIME_CLASS(GalleryUpload)))
		return 1;   // if cf is not valid

	cf->PerformPost();
	cf->PostMessageW(WM_USER_RENDER_COMPLETE, 0, 0);
	return 0;
}

UINT GalleryUpload::TagsControllingFunction(LPVOID pParam)
{
	HWND hDlg = reinterpret_cast<HWND>(pParam);
	HINTERNET hInetInit = nullptr;
	HINTERNET hInetCnxn = nullptr;
	HINTERNET hInetReq = nullptr;

	hInetInit = ::InternetOpen(L"Context Free", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);

	if (hInetInit)
		hInetCnxn = ::InternetConnect(hInetInit, L"www.contextfreeart.org",
			INTERNET_DEFAULT_HTTPS_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, NULL);

	if (hInetCnxn)
		hInetReq = ::HttpOpenRequest(hInetCnxn, L"GET", L"/gallery/tags.php?t=tags", L"HTTP/1.1",
			NULL, NULL, INTERNET_FLAG_KEEP_CONNECTION | INTERNET_FLAG_SECURE, NULL);

	if (hInetReq && ::HttpSendRequest(hInetReq, NULL, 0, NULL, 0)) {
		DWORD length = sizeof(DWORD);
		DWORD status = 0;
		HttpQueryInfo(hInetReq, HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER,
			&status, &length, NULL);
		if (status == 200) {
			char buf[200];
			DWORD bytesRead;
			std::string response;
			while (::InternetReadFile(hInetReq, (LPVOID)buf, 200, &bytesRead) && bytesRead) {
				response.append(buf, bytesRead);
				bytesRead = 0;
			}

			if (!response.empty()) {
				AllTags = Upload::AllTags(response.c_str(), response.length());
				for (const auto& tag : AllTags)
					AllTagsL.insert(Utf8ToUtf16(tag.c_str()));
				::PostMessageW(hDlg, WM_USER_RENDER_COMPLETE, 1, 0);
			}
		}

	}

	if (hInetReq)
		::InternetCloseHandle(hInetReq);
	if (hInetCnxn)
		::InternetCloseHandle(hInetCnxn);
	if (hInetInit)
		::InternetCloseHandle(hInetInit);

	return 0;
}

void GalleryUpload::PerformPost()
{
	HINTERNET hInetInit = nullptr;
	HINTERNET hInetCnxn = nullptr;

	std::wstring header = Utf8ToUtf16(Upload::generateContentType().c_str());
	header.insert(0, L"Content-Type: ");

	hInetInit = ::InternetOpen(L"Context Free", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);

	if (hInetInit)
		hInetCnxn = ::InternetConnect(hInetInit, L"www.contextfreeart.org",
			INTERNET_DEFAULT_HTTPS_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, NULL);

	if (hInetCnxn)
		m_hInetPost = ::HttpOpenRequest(hInetCnxn, L"POST", L"/gallery/upload.php", L"HTTP/1.1",
			NULL, NULL, INTERNET_FLAG_KEEP_CONNECTION | INTERNET_FLAG_SECURE, NULL);

	if (m_hInetPost && ::HttpSendRequest(m_hInetPost, header.c_str(), (DWORD)header.length(),
		(LPVOID)m_sPayload.data(), (DWORD)m_sPayload.length())) 
	{
		char buf[200];
		DWORD bytesRead;
		std::string response;
		while (::InternetReadFile(m_hInetPost, (LPVOID)buf, 200, &bytesRead) && bytesRead) {
			response.append(buf, bytesRead);
			bytesRead = 0;
		}

		DWORD length = sizeof(DWORD);
		HttpQueryInfo(m_hInetPost, HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER,
			&m_iHttpStatus, &length, NULL);

		if (m_iHttpStatus == 200) {
			Upload upload(response.c_str(), response.length());
			m_iDesignID = upload.mId;
		} else {
			auto start = response.find("<p id='AFD8D2F0-B6EB-4569-9D89-954604507F3B'>");
			if (start != std::string::npos)
				response.erase(0, start + 45);
			auto end = response.rfind("</p>");
			if (end != std::string::npos)
				response.erase(end);
			m_sErrorMessage = std::move(response);
		}
	} else {
		m_iRequestError = GetLastError();
	}

	if (m_hInetPost)
		::InternetCloseHandle(m_hInetPost);
	m_hInetPost = nullptr;
	if (hInetCnxn)
		::InternetCloseHandle(hInetCnxn);
	if (hInetInit)
		::InternetCloseHandle(hInetInit);
}

LRESULT GalleryUpload::UploadDone(WPARAM wParam, LPARAM lParam)
{
	if (m_bShouldClose) {
		OnOK();
		return 0;
	}

	if (wParam == 1) {
		TagsLoaded = true;
		InitTagsAC();
		return 0;
	}

	if (m_iDesignID) {
		m_ctrlCancel.SetWindowTextW(L"See Design");
		m_ctrlCancel.SetMouseCursorHand();
		m_ctrlUpload.SetWindowTextW(L"Done");
		m_ctrlUpload.EnableWindow();
	} else {
		m_ctrlUpload.SetWindowTextW(L"Upload");
		m_ctrlUpload.EnableWindow();
		if (!m_sErrorMessage.empty()) {
			::MessageBox(GetSafeHwnd(), Utf8ToUtf16(m_sErrorMessage.c_str()).c_str(),
				L"Upload Failed", MB_ICONASTERISK);
			m_sErrorMessage.clear();
		} else {
			if (m_iRequestError >= 12000) {
				::MessageBox(GetSafeHwnd(), L"Internet error",
					L"Upload Failed", MB_ICONASTERISK);
			} else {
				::MessageBox(GetSafeHwnd(), L"Unknown error",
					L"Upload Failed", MB_ICONASTERISK);
			}
			m_iRequestError = 0;
		}
	}
	return 0;
}

void GalleryUpload::OnCancel()
{
	if (m_hInetPost) {
		::InternetCloseHandle(m_hInetPost);
		m_hInetPost = nullptr;
		return;
	}
	if (m_iDesignID) {
		CString url;
		url.Format(L"https://www.contextfreeart.org/gallery/view.php?id=%d", m_iDesignID);
		ShellExecute(NULL, L"open", url, NULL, NULL, SW_SHOWNORMAL);
	}

	CDialogEx::OnCancel();
}

void GalleryUpload::OnClose()
{
	if (m_hInetPost) {
		::InternetCloseHandle(m_hInetPost);
		m_hInetPost = nullptr;
		m_bShouldClose = true;
		return;
	}

	CDialogEx::OnClose();
}

void GalleryUpload::OnSelchangeTaglist()
{
	if (auto lock = EditLock()) {
		if (m_eTagMoveDirection == TagMoveDirection::AddToList) {
			m_ctrlTagMove.SetWindowTextW(L"◄");
			m_ctrlToolTip.UpdateTipText(L"Add tag to tags list", &m_ctrlTagMove, IDC_TAGMOVE);
			m_eTagMoveDirection = TagMoveDirection::DeleteFromList;
		}
	}
}

void GalleryUpload::OnEditchangeTag()
{
	if (auto lock = EditLock()) {
		if (m_eTagMoveDirection == TagMoveDirection::DeleteFromList) {
			m_ctrlTagMove.SetWindowTextW(L"►");
			m_ctrlToolTip.UpdateTipText(L"Remove tag from tags list", &m_ctrlTagMove, IDC_TAGMOVE);
			m_eTagMoveDirection = TagMoveDirection::AddToList;
		}
		CString newTag;
		m_ctrlTagEdit.GetWindowTextW(newTag);
		if (newTag.FindOneOf(L" \r\n\t\f") == -1) {
			m_sCurrentTag = newTag;
		} else {
			::MessageBeep(MB_ICONERROR);
			m_ctrlTagEdit.SetWindowTextW(m_sCurrentTag);
		}
	}
}

void GalleryUpload::OnClickedTagMove()
{
	if (m_eTagMoveDirection == TagMoveDirection::AddToList) {
		CString tag;
		m_ctrlTagEdit.GetWindowTextW(tag);
		if (!tag.IsEmpty()) {
			if (m_ctrlTagsList.FindStringExact(-1, tag) == CB_ERR)
				m_ctrlTagsList.AddString(tag);
			EditLock lock;
			m_ctrlTagsList.SelectString(-1, tag);
			m_ctrlTagEdit.SetEditSel(0, -1);
			m_ctrlTagEdit.Clear();
		}
	} else {
		int sel = m_ctrlTagsList.GetCurSel();
		if (sel != CB_ERR) {
			m_ctrlTagsList.DeleteString(sel);
			m_ctrlTagsList.SetCurSel(-1);
		}
	}
}

BOOL GalleryUpload::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_LBUTTONDOWN ||
		pMsg->message == WM_LBUTTONUP ||
		pMsg->message == WM_MOUSEMOVE)
	{
		m_ctrlToolTip.RelayEvent(pMsg);
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
