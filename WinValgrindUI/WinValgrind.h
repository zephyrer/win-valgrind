// WinValgrind.h : main header file for the WinValgrind application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CWinValgrindApp:
// See WinValgrind.cpp for the implementation of this class
//

class CWinValgrindApp : public CWinApp
{
public:
	CWinValgrindApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CWinValgrindApp theApp;