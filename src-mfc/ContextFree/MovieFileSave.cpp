#include "pch.h"
#include "ContextFree.h"
#include "MovieFileSave.h"
#include <format>
#include "RenderParams.h"

namespace {
	BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
	{
		DWORD processId;
		GetWindowThreadProcessId(hwnd, &processId);

		if (lParam == processId)
			PostMessage(hwnd, WM_CLOSE, 0, 0);
		return TRUE;
	}
}

IMPLEMENT_DYNAMIC(MovieFileSave, CFileDialog)



MovieFileSave::MovieFileSave(std::wstring& temp, LPCTSTR name, BOOL loop, RenderParameters& p)
	: CFileDialog(FALSE, p.Codec == RenderParameters::Codecs::GIF ? _T("gif") : _T("mov"), 
		name, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		p.Codec == RenderParameters::Codecs::GIF ?
		_T("GIF files (*.gif)|*.gif|All files (*.*)|*.*||") :
		_T("MOV files (*.mov)|*.mov|All files (*.*)|*.*||")),
		processInfo{},
		m_sTempName(temp),
		m_bLoop(loop),
		m_sParams(p)
{
	AddPushButton(IDC_PREVIEW, _T("Preview"));
	if (p.Codec != RenderParameters::Codecs::GIF)
		AddCheckButton(IDC_PREVIEWLOOP, _T("Loop preview"), loop);
}

MovieFileSave::~MovieFileSave()
{
	if (processInfo.dwProcessId)
		::EnumWindows(&EnumWindowsProc, processInfo.dwProcessId);
}

void MovieFileSave::OnButtonClicked(DWORD dwIDCtl)
{
	if (dwIDCtl == IDC_PREVIEW) {
		SetControlState(IDC_PREVIEW, CDCONTROLSTATEF::CDCS_INACTIVE);
		if (m_sParams.Codec != RenderParameters::Codecs::GIF)
			SetControlState(IDC_PREVIEWLOOP, CDCONTROLSTATEF::CDCS_INACTIVE);

		TCHAR szFileName[MAX_PATH];
		::GetModuleFileNameW(NULL, szFileName, MAX_PATH);
		std::wstring app = szFileName;
		auto it = app.find_last_of(L'\\');
		app.resize(it + 1);
		app.append(L"ffplay.exe");

		std::wstring loopStr;
		if (m_sParams.Codec == RenderParameters::Codecs::GIF)
			loopStr = std::format(L"-loop {}", m_sParams.MovieLoops);
		else
			loopStr = m_bLoop ? L"-loop 0" : L"";
		std::wstring args = std::format(L"\"{}\" {} \"{}\"", app, loopStr, m_sTempName);
		STARTUPINFOW startupInfo = { sizeof(STARTUPINFO) };
		if (!::CreateProcessW(app.c_str(), args.data(), NULL, NULL, FALSE, 
			CREATE_NO_WINDOW, NULL, NULL, &startupInfo, &processInfo))
		{
			TRACE1("Preview failed: %d\n", GetLastError());
		}
	}
}

void MovieFileSave::OnCheckButtonToggled(DWORD dwIDCtl, BOOL bChecked)
{
	if (dwIDCtl == IDC_PREVIEWLOOP)
		m_bLoop = bChecked;
}

BEGIN_MESSAGE_MAP(MovieFileSave, CFileDialog)
END_MESSAGE_MAP()
