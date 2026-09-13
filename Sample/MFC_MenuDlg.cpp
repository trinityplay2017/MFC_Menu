#include "stdafx.h"
#include "MFC_Menu.h"
#include "MFC_MenuDlg.h"
#include "../Source/NewMenu.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CMFC_MenuDlg::CMFC_MenuDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(IDD_MFC_MENU_DIALOG, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    if (m_hIcon == NULL)
        m_hIcon = AfxGetApp()->LoadStandardIcon(IDI_APPLICATION);

    m_hIconNew   = NULL;
    m_hIconOpen  = NULL;
    m_hIconSave  = NULL;
    m_hIconExit  = NULL;
    m_hIconAbout = NULL;
}

void CMFC_MenuDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFC_MenuDlg, CDialogEx)
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BTN_SHOWMENU, &CMFC_MenuDlg::OnBnClickedBtnShowmenu)
    ON_COMMAND(ID_CMD_NEW,   &CMFC_MenuDlg::OnCmdNew)
    ON_COMMAND(ID_CMD_OPEN,  &CMFC_MenuDlg::OnCmdOpen)
    ON_COMMAND(ID_CMD_SAVE,  &CMFC_MenuDlg::OnCmdSave)
    ON_COMMAND(ID_CMD_EXIT,  &CMFC_MenuDlg::OnCmdExit)
    ON_COMMAND(ID_CMD_ABOUT, &CMFC_MenuDlg::OnCmdAbout)
END_MESSAGE_MAP()

BOOL CMFC_MenuDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    SetIcon(m_hIcon, TRUE);
    SetIcon(m_hIcon, FALSE);

    // Load some system icons for demonstration
    m_hIconNew   = (HICON)LoadImage(NULL, IDI_APPLICATION, IMAGE_ICON, 16, 16, LR_SHARED);
    m_hIconOpen  = (HICON)LoadImage(NULL, IDI_INFORMATION, IMAGE_ICON, 16, 16, LR_SHARED);
    m_hIconSave  = (HICON)LoadImage(NULL, IDI_WARNING,     IMAGE_ICON, 16, 16, LR_SHARED);
    m_hIconExit  = (HICON)LoadImage(NULL, IDI_ERROR,       IMAGE_ICON, 16, 16, LR_SHARED);
    m_hIconAbout = (HICON)LoadImage(NULL, IDI_QUESTION,    IMAGE_ICON, 16, 16, LR_SHARED);

    return TRUE;
}

void CMFC_MenuDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this);
        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialogEx::OnPaint();
    }
}

HCURSOR CMFC_MenuDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

// ------------------------------------------------------------
// Show the custom owner-draw popup menu
// ------------------------------------------------------------
void CMFC_MenuDlg::OnBnClickedBtnShowmenu()
{
    CNewMenu menu;
    menu.CreatePopupMenu();

    // Optional: customise appearance
    menu.SetColors(
        RGB(45, 45, 48),      // background
        RGB(0, 122, 204),     // hover (VS blue)
        RGB(241, 241, 241),   // text
        RGB(128, 128, 128),   // disabled
        RGB(70, 70, 74));     // separator

    menu.SetFont(_T("Segoe UI"), 15);
    menu.SetIconSize(16, 16);
    menu.SetLeftWidth(28);
    menu.SetItemHeight(30);
    menu.SetMenuWidth(220);
    menu.EnableIcons(TRUE);

    // Build menu
    menu.AddMenuItem(ID_CMD_NEW,  _T("New File"),    _T("Ctrl+N"), m_hIconNew);
    menu.AddMenuItem(ID_CMD_OPEN, _T("Open File"),   _T("Ctrl+O"), m_hIconOpen);
    menu.AddMenuItem(ID_CMD_SAVE, _T("Save"),        _T("Ctrl+S"), m_hIconSave);
    menu.AddSeparator();

    // Sub-menu example
    CNewMenu subMenu;
    subMenu.CreatePopupMenu();
    subMenu.SetColors(RGB(45,45,48), RGB(0,122,204), RGB(241,241,241), RGB(128,128,128), RGB(70,70,74));
    subMenu.SetFont(_T("Segoe UI"), 15);
    subMenu.SetItemHeight(28);
    subMenu.SetMenuWidth(180);
    subMenu.AddMenuItem(ID_CMD_ABOUT, _T("About..."), NULL, m_hIconAbout);

    menu.AddSubMenu(_T("Help"), &subMenu, m_hIconAbout);
    menu.AddSeparator();
    menu.AddMenuItem(ID_CMD_EXIT, _T("Exit"), _T("Alt+F4"), m_hIconExit);

    // Display at cursor
    CPoint pt;
    GetCursorPos(&pt);
    menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this);
}

void CMFC_MenuDlg::OnCmdNew()
{
    AfxMessageBox(_T("New File selected"));
}

void CMFC_MenuDlg::OnCmdOpen()
{
    AfxMessageBox(_T("Open File selected"));
}

void CMFC_MenuDlg::OnCmdSave()
{
    AfxMessageBox(_T("Save selected"));
}

void CMFC_MenuDlg::OnCmdExit()
{
    EndDialog(IDCANCEL);
}

void CMFC_MenuDlg::OnCmdAbout()
{
    AfxMessageBox(_T("MFC Custom Owner-Draw Menu Demo\nCNewMenu class"));
}
