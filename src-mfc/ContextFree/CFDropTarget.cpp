#include "pch.h"
#include "CFDropTarget.h"
#include "MainFrm.h"

CFDropTarget::CFDropTarget(CMainFrame& mf)
: COleDropTarget()
, m_hMainFrame(mf)
{
}

DROPEFFECT CFDropTarget::OnDragEnter(CWnd*, COleDataObject* pDataObject, DWORD, CPoint)
{
    return m_hMainFrame.OnDragEnter(pDataObject);
}

DROPEFFECT CFDropTarget::OnDragOver(CWnd*, COleDataObject* pDataObject, DWORD, CPoint)
{
    return m_hMainFrame.OnDragOver(pDataObject);
}

BOOL CFDropTarget::OnDrop(CWnd*, COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint)
{
    return m_hMainFrame.OnDrop(pDataObject, dropEffect);
}

