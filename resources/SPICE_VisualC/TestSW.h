// TestSW.h : main header file for the TESTSW application
//

#if !defined(AFX_TESTSW_H__B3001464_CA01_11D5_A00E_00C0DF019CE8__INCLUDED_)
#define AFX_TESTSW_H__B3001464_CA01_11D5_A00E_00C0DF019CE8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


/////////////////////////////////////////////////////////////////////////////
// CTestSWApp:
// See TestSW.cpp for the implementation of this class
//

class CTestSWApp : public CWinApp
{
public:
//	HINSTANCE hDLL;
	CTestSWApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestSWApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestSWApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//1*******************************************************************************************
				//Declaration global typs and constants

//1*******************************************************************************************

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTSW_H__B3001464_CA01_11D5_A00E_00C0DF019CE8__INCLUDED_)
