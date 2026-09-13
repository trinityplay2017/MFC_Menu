#pragma once

#include <afxwin.h>
#include <string>

// Item type enumeration
enum ITEMTYPE
{
    ITEMTYPE_STRING = 0,
    ITEMTYPE_SEPARATOR,
    ITEMTYPE_SUBMENU
};

// Data attached to every owner-draw menu item (stored in itemData)
struct StruItemInfo
{
    ITEMTYPE    eItemType;
    CString     strText;
    CString     strShortcut;
    HICON       hIcon;

    StruItemInfo()
        : eItemType(ITEMTYPE_STRING)
        , hIcon(NULL)
    {
    }
};

// ============================================================
// CNewMenu - Self-drawing owner-draw popup / menu bar class
// ============================================================
class CNewMenu : public CMenu
{
public:
    CNewMenu();
    virtual ~CNewMenu();

    // Create a popup menu
    BOOL CreatePopupMenu();

    // Configuration
    void SetColors(COLORREF clrBk, COLORREF clrBkHover,
                   COLORREF clrText, COLORREF clrTextDisable,
                   COLORREF clrSeparator);
    void SetFont(LPCTSTR lpszFaceName, int nFontSize);
    void SetIconSize(int nWidth, int nHeight);
    void SetLeftWidth(int nWidth);          // width of the icon column
    void SetItemHeight(int nHeight);
    void SetSeparatorHeight(int nHeight);
    void SetMenuWidth(int nWidth);
    void EnableIcons(BOOL bEnable = TRUE);

    // Add helpers (all items become MF_OWNERDRAW)
    BOOL AddMenuItem(UINT nID, LPCTSTR lpszText,
                     LPCTSTR lpszShortcut = NULL, HICON hIcon = NULL);
    BOOL AddSeparator();
    BOOL AddSubMenu(LPCTSTR lpszText, CNewMenu* pSubMenu, HICON hIcon = NULL);

    // CMenu overrides
    virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
    virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
    virtual void DeleteItem(LPDELETEITEMSTRUCT lpDeleteItemStruct);

protected:
    // Internal helper to append an owner-draw item
    BOOL AppendOwnerDrawItem(UINT nFlags, UINT_PTR nIDNewItem, StruItemInfo* pInfo);

    // Appearance
    COLORREF    m_clrBk;
    COLORREF    m_clrBkHover;
    COLORREF    m_clrText;
    COLORREF    m_clrTextDisable;
    COLORREF    m_clrSeparator;

    int         m_nLeftWidth;       // left column width (icons)
    int         m_nIconWidth;
    int         m_nIconHeight;
    int         m_nFontSize;
    int         m_nSeparatorHeight;
    int         m_nItemHeight;
    int         m_nMenuWidth;

    std::wstring m_strFontFaceName;
    BOOL        m_bHasIcon;
};
