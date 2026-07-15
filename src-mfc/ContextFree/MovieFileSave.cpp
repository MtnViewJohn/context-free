#include "pch.h"
#include "ContextFree.h"
#include "MovieFileSave.h"
#include <format>
#include "RenderParams.h"
#include <map>

namespace {
	BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
	{
		DWORD processId;
		GetWindowThreadProcessId(hwnd, &processId);

		if (lParam == processId)
			PostMessage(hwnd, WM_CLOSE, 0, 0);
		return TRUE;
	}

	std::map<RenderParameters::Codecs, const wchar_t*> extMap =
	{
		{ RenderParameters::Codecs::H264,   L"mov"},
		{ RenderParameters::Codecs::ProRes, L"mov"},
		{ RenderParameters::Codecs::GIF,    L"gif"},
		{ RenderParameters::Codecs::PNG,    L"png" },
	};
	std::map<RenderParameters::Codecs, const wchar_t*> filterMap =
	{
		{ RenderParameters::Codecs::H264,   L"MOV files (*.mov)|*.mov|All files (*.*)|*.*||"},
		{ RenderParameters::Codecs::ProRes, L"MOV files (*.mov)|*.mov|All files (*.*)|*.*||"},
		{ RenderParameters::Codecs::GIF,    L"GIF files(*.gif)|*.gif|All files(*.*)|*.*||"},
		{ RenderParameters::Codecs::PNG,    L"PNG files(*.png)|*.png||" },
	};
	std::map<RenderParameters::Codecs, DWORD> flagMap =
	{
		{ RenderParameters::Codecs::H264,   OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT},
		{ RenderParameters::Codecs::ProRes, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT},
		{ RenderParameters::Codecs::GIF,    OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT},
		{ RenderParameters::Codecs::PNG,    OFN_HIDEREADONLY},
	};
}

IMPLEMENT_DYNAMIC(MovieFileSave, CFileDialog)



MovieFileSave::MovieFileSave(std::wstring& temp, LPCTSTR name, BOOL loop, RenderParameters& p)
	: CFileDialog(FALSE, extMap[p.Codec], name, flagMap[p.Codec], filterMap[p.Codec]),
		processInfo{},
		m_sTempName(temp),
		m_bLoop(loop),
		m_sParams(p)
{
	if (p.Codec == RenderParameters::Codecs::PNG) {
		AddText(IDC_LENGTH, L"In the template, %f expands to the frame number. %v & %V expand to the variation");
		m_ofn.lpstrTitle = L"Select PNG frame Save Template";
	}
	AddPushButton(IDC_PREVIEW, _T("Preview"));
	if (p.Codec != RenderParameters::Codecs::GIF)
		AddCheckButton(IDC_PREVIEWLOOP, _T("Loop preview"), loop);
	if (::PathIsDirectoryW(temp.c_str()))
		m_sTempName += L"\\%04d.png";
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

		std::wstring rateStr;
		if (m_sParams.Codec == RenderParameters::Codecs::PNG)
			rateStr = std::format(L"-framerate {}", m_sParams.MovieFrameRate);

		std::wstring args = std::format(L"\"{}\" {} {} \"{}\"", app, loopStr, rateStr, m_sTempName);
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
