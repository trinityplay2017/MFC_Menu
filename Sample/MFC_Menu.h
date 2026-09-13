#pragma once

#ifndef __AFXWIN_H__
    #error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"

class CMFC_MenuApp : public CWinApp
{
public:
    CMFC_MenuApp();

public:
    virtual BOOL InitInstance();

    DECLARE_MESSAGE_MAP()
};

extern CMFC_MenuApp theApp;
