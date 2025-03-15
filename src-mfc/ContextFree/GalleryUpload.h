#pragma once
#include "afxdialogex.h"
#include "UploadParams.h"
#include <wininet.h>

// GalleryUpload dialog

class UploadParams;
class CChildFrame;

class GalleryUpload : public CDialogEx
{
	DECLARE_DYNAMIC(GalleryUpload)

public:
	GalleryUpload(CChildFrame& child, UploadParams& params, CWnd* pParent = nullptr);   // standard constructor
	virtual ~GalleryUpload();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UPLOAD };
#endif

protected:
	enum class TagMoveDirection { AddToList, DeleteFromList };
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	CChildFrame& m_rChild;
	UploadParams& m_rParams;
	int m_iCurrentLicense = 0;
	int m_iInitialLicense = 0;
	void PerformPost();
	std::string m_sPayload;
	std::string m_sErrorMessage;
	unsigned int m_iDesignID = 0;
	DWORD m_iHttpStatus = 0;
	DWORD m_iRequestError = 0;
	HINTERNET m_hInetPost = nullptr;
	HANDLE m_hRenderThread = nullptr;
	static UINT UploadControllingFunction(LPVOID pParam);
	bool m_bShouldClose = false;
	static std::atomic_bool TagsLoaded;
	static UINT TagsControllingFunction(LPVOID pParam);
	void InitTagsAC();
	TagMoveDirection m_eTagMoveDirection = TagMoveDirection::AddToList;
	CString m_sCurrentTag;
	CToolTipCtrl m_ctrlToolTip;

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString m_sUsername;
	CString m_sPassword;
	CString m_sTitle;
	CString m_sNotes;
	afx_msg void OnClickedAccount();
	CString m_sFilename;
	CSpinButtonCtrl m_ctrlWidthSpin;
	CSpinButtonCtrl m_ctrlHeightSpin;
	CString m_sVariation;
	BOOL m_iJPEGPNG;
	CButton m_ctrlCropTile;
	CComboBox m_ctrlLicense;
	CString m_sCCname;
	CMFCButton m_ctrlCCimage;
	afx_msg void OnClickedccImage();
	afx_msg void OnSelchangeLicense();
	afx_msg LRESULT UploadDone(WPARAM wParam, LPARAM lParam);
	CStatic m_ctrlMult1;
	CStatic m_ctrlMult2;
	CStatic m_ctrlMult3;
	CEdit m_ctrlMultWidth;
	CEdit m_ctrlMultHeight;
	afx_msg void OnClickedUpload();
	CMFCButton m_ctrlUpload;
	CMFCButton m_ctrlCancel;
	virtual void OnCancel();
	CMFCButton m_ctrlAccount;
	afx_msg void OnClose();
	CComboBox m_ctrlTagEdit;
	CComboBox m_ctrlTagsList;
	CButton m_ctrlTagMove;
	afx_msg void OnSelchangeTaglist();
	afx_msg void OnEditchangeTag();
	afx_msg void OnClickedTagMove();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
