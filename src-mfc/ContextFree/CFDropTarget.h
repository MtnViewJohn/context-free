#pragma once
#include <afxole.h>

class CMainFrame;

class CFDropTarget : public COleDropTarget
{
public:
    CFDropTarget(CMainFrame& mf);
    DROPEFFECT OnDragEnter(CWnd* pWnd, COleDataObject* pDataObject, 
                           DWORD dwKeyState, CPoint point) override;
    DROPEFFECT OnDragOver(CWnd* pWnd, COleDataObject* pDataObject,
                          DWORD dwKeyState, CPoint point) override;
    BOOL OnDrop(CWnd* pWnd, COleDataObject* pDataObject,
                DROPEFFECT dropEffect, CPoint point) override;
protected:
    CMainFrame& m_hMainFrame;
};

