#include "stdafx.h"
#include "NewMenu.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ------------------------------------------------------------
// Construction / Destruction
// ------------------------------------------------------------
CNewMenu::CNewMenu()
{
    // Default modern dark-ish palette (can be changed)
    m_clrBk           = RGB(45, 45, 48);
    m_clrBkHover      = RGB(62, 62, 66);
    m_clrText         = RGB(241, 241, 241);
    m_clrTextDisable  = RGB(128, 128, 128);
    m_clrSeparator    = RGB(70, 70, 74);

    m_nLeftWidth      = 28;
    m_nIconWidth      = 16;
    m_nIconHeight     = 16;
    m_nFontSize       = 16;          // logical height
    m_nSeparatorHeight= 9;
    m_nItemHeight     = 28;
    m_nMenuWidth      = 200;

    m_strFontFaceName = L"Segoe UI";
    m_bHasIcon        = TRUE;
}

CNewMenu::~CNewMenu()
{
    // CMenu will call DeleteItem for remaining items when destroyed
    DestroyMenu();
}

// ------------------------------------------------------------
// Create
// ------------------------------------------------------------
BOOL CNewMenu::CreatePopupMenu()
{
    return CMenu::CreatePopupMenu();
}

// ------------------------------------------------------------
// Configuration setters
// ------------------------------------------------------------
void CNewMenu::SetColors(COLORREF clrBk, COLORREF clrBkHover,
                         COLORREF clrText, COLORREF clrTextDisable,
                         COLORREF clrSeparator)
{
    m_clrBk          = clrBk;
    m_clrBkHover     = clrBkHover;
    m_clrText        = clrText;
    m_clrTextDisable = clrTextDisable;
    m_clrSeparator   = clrSeparator;
}

void CNewMenu::SetFont(LPCTSTR lpszFaceName, int nFontSize)
{
    m_strFontFaceName = lpszFaceName;
    m_nFontSize       = nFontSize;
}

void CNewMenu::SetIconSize(int nWidth, int nHeight)
{
    m_nIconWidth  = nWidth;
    m_nIconHeight = nHeight;
}

void CNewMenu::SetLeftWidth(int nWidth)
{
    m_nLeftWidth = nWidth;
}

void CNewMenu::SetItemHeight(int nHeight)
{
    m_nItemHeight = nHeight;
}

void CNewMenu::SetSeparatorHeight(int nHeight)
{
    m_nSeparatorHeight = nHeight;
}

void CNewMenu::SetMenuWidth(int nWidth)
{
    m_nMenuWidth = nWidth;
}

void CNewMenu::EnableIcons(BOOL bEnable)
{
    m_bHasIcon = bEnable;
}

// ------------------------------------------------------------
// Add helpers
// ------------------------------------------------------------
BOOL CNewMenu::AppendOwnerDrawItem(UINT nFlags, UINT_PTR nIDNewItem, StruItemInfo* pInfo)
{
    nFlags |= MF_OWNERDRAW;
    return AppendMenu(nFlags, nIDNewItem, (LPCTSTR)pInfo);
}

BOOL CNewMenu::AddMenuItem(UINT nID, LPCTSTR lpszText,
                           LPCTSTR lpszShortcut /*= NULL*/, HICON hIcon /*= NULL*/)
{
    StruItemInfo* pInfo = new StruItemInfo;
    pInfo->eItemType  = ITEMTYPE_STRING;
    pInfo->strText    = lpszText;
    if (lpszShortcut)
        pInfo->strShortcut = lpszShortcut;
    pInfo->hIcon = hIcon;

    return AppendOwnerDrawItem(MF_STRING, nID, pInfo);
}

BOOL CNewMenu::AddSeparator()
{
    StruItemInfo* pInfo = new StruItemInfo;
    pInfo->eItemType = ITEMTYPE_SEPARATOR;

    return AppendOwnerDrawItem(MF_SEPARATOR, 0, pInfo);
}

BOOL CNewMenu::AddSubMenu(LPCTSTR lpszText, CNewMenu* pSubMenu, HICON hIcon /*= NULL*/)
{
    if (!pSubMenu)
        return FALSE;

    StruItemInfo* pInfo = new StruItemInfo;
    pInfo->eItemType = ITEMTYPE_SUBMENU;
    pInfo->strText   = lpszText;
    pInfo->hIcon     = hIcon;

    // For popup items the ID is the HMENU of the sub-menu
    return AppendOwnerDrawItem(MF_POPUP, (UINT_PTR)pSubMenu->m_hMenu, pInfo);
}

// ------------------------------------------------------------
// MeasureItem  (exactly matching the supplied logic)
// ------------------------------------------------------------
void CNewMenu::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
    StruItemInfo* pStruItemInfo = (StruItemInfo*)lpMeasureItemStruct->itemData;
    if (pStruItemInfo == NULL)
        return;

    if (pStruItemInfo->eItemType == ITEMTYPE_SEPARATOR)
    {
        // Sets the height of the Separator
        lpMeasureItemStruct->itemHeight = m_nSeparatorHeight;
    }
    else
    {
        lpMeasureItemStruct->itemHeight = m_nItemHeight;
    }
    // Setting item width
    lpMeasureItemStruct->itemWidth = m_nMenuWidth;
}

// ------------------------------------------------------------
// DrawItem  (exactly matching the supplied logic + small polish)
// ------------------------------------------------------------
void CNewMenu::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
    CString strText;
    CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC); // Gets the device handle to the menu item
    StruItemInfo* pStruItemInfo = (StruItemInfo*)lpDrawItemStruct->itemData;
    if (pStruItemInfo == NULL)
    {
        return;
    }

    CRect rect(lpDrawItemStruct->rcItem);

    if (pStruItemInfo->eItemType == ITEMTYPE_SEPARATOR) // Separator
    {
        // Draw background
        pDC->FillSolidRect(rect, m_clrBk);

        // Draw separator line
        CRect rcSeparator(rect);
        rcSeparator.top    = rcSeparator.top + rcSeparator.Height() / 2;
        rcSeparator.bottom = rcSeparator.top + 1;
        rcSeparator.left  += 5;
        rcSeparator.right -= 5;
        pDC->Draw3dRect(rcSeparator, m_clrSeparator, m_clrSeparator);
    }
    else
    {
        // Draw background according to state
        if (lpDrawItemStruct->itemState & ODS_GRAYED) // Disabled
        {
            pDC->FillSolidRect(rect, m_clrBk);
            pDC->SetTextColor(m_clrTextDisable);
        }
        else if (lpDrawItemStruct->itemState & ODS_SELECTED)
        {
            // Paint the background color of the rectangular box on the menu item
            pDC->FillSolidRect(rect, m_clrBkHover);
            // Set menu text color
            pDC->SetTextColor(m_clrText);
        }
        else
        {
            pDC->FillSolidRect(rect, m_clrBk);
            pDC->SetTextColor(m_clrText);
        }

        pDC->SetBkMode(TRANSPARENT);

        // Icon rectangle
        CRect rcIcon(rect);
        rcIcon.left  += (m_nLeftWidth - m_nIconWidth) / 2;
        rcIcon.right  = rcIcon.left + m_nIconWidth;
        rcIcon.top   += (rcIcon.Height() - m_nIconHeight) / 2;

        if (pStruItemInfo->hIcon != NULL)
        {
            DrawIconEx(pDC->m_hDC, rcIcon.left, rcIcon.top,
                       pStruItemInfo->hIcon, m_nIconWidth, m_nIconHeight,
                       0, NULL, DI_NORMAL);
        }

        // Text font and size Settings
        LOGFONT fontInfo;
        pDC->GetCurrentFont()->GetLogFont(&fontInfo);

        fontInfo.lfHeight = -m_nFontSize;   // negative = character height
        lstrcpy(fontInfo.lfFaceName, m_strFontFaceName.c_str());
        CFont fontCh;
        fontCh.CreateFontIndirect(&fontInfo);
        CFont* pOldFont = pDC->SelectObject(&fontCh);

        CRect rcText(rect);
        if (m_bHasIcon)
        {
            rcText.left += m_nLeftWidth;
        }
        else
        {
            rcText.left += 10;
        }
        rcText.top    += (rcText.Height() - m_nFontSize) / 2;
        rcText.bottom  = rcText.top + m_nFontSize;

        // Sub menu item or normal string
        if (pStruItemInfo->eItemType == ITEMTYPE_SUBMENU)
        {
            pDC->TextOut(rcText.left, rcText.top,
                         pStruItemInfo->strText, pStruItemInfo->strText.GetLength());

            // Draw a simple right arrow for sub-menu
            CRect rcArrow = rect;
            rcArrow.left = rcArrow.right - 18;
            pDC->TextOut(rcArrow.left, rcText.top, _T(">"));
        }
        else if (pStruItemInfo->eItemType == ITEMTYPE_STRING)
        {
            // Main text
            pDC->TextOut(rcText.left, rcText.top,
                         pStruItemInfo->strText, pStruItemInfo->strText.GetLength());

            // Shortcut on the right
            if (!pStruItemInfo->strShortcut.IsEmpty())
            {
                CSize sz = pDC->GetTextExtent(pStruItemInfo->strShortcut);
                int x = rect.right - sz.cx - 12;
                pDC->TextOut(x, rcText.top,
                             pStruItemInfo->strShortcut, pStruItemInfo->strShortcut.GetLength());
            }
        }

        pDC->SelectObject(pOldFont);
    }
}

// ------------------------------------------------------------
// DeleteItem - free the StruItemInfo we allocated
// ------------------------------------------------------------
void CNewMenu::DeleteItem(LPDELETEITEMSTRUCT lpDeleteItemStruct)
{
    if (lpDeleteItemStruct->itemData != 0)
    {
        StruItemInfo* pInfo = (StruItemInfo*)lpDeleteItemStruct->itemData;
        delete pInfo;
        lpDeleteItemStruct->itemData = 0;
    }
    CMenu::DeleteItem(lpDeleteItemStruct);
}
