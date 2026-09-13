#include "stdafx.h"
#include "MFC_Menu.h"
#include "MFC_MenuDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CMFC_MenuApp, CWinApp)
END_MESSAGE_MAP()

CMFC_MenuApp::CMFC_MenuApp()
{
}

CMFC_MenuApp theApp;

BOOL CMFC_MenuApp::InitInstance()
{
    CWinApp::InitInstance();

    // Standard initialization
    AfxEnableControlContainer();

    CMFC_MenuDlg dlg;
    m_pMainWnd = &dlg;
    INT_PTR nResponse = dlg.DoModal();

    return FALSE;
}
