#pragma once

#include "../Source/NewMenu.h"

class CMFC_MenuDlg : public CDialogEx
{
public:
    CMFC_MenuDlg(CWnd* pParent = NULL);

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_MFC_MENU_DIALOG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();

    HICON m_hIcon;

    // Demo icons (loaded from system)
    HICON m_hIconNew;
    HICON m_hIconOpen;
    HICON m_hIconSave;
    HICON m_hIconExit;
    HICON m_hIconAbout;

    afx_msg void OnBnClickedBtnShowmenu();
    afx_msg void OnCmdNew();
    afx_msg void OnCmdOpen();
    afx_msg void OnCmdSave();
    afx_msg void OnCmdExit();
    afx_msg void OnCmdAbout();
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();

    DECLARE_MESSAGE_MAP()
};
