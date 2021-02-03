//						Raylase AG
//				Test sample for SP-ICE
//											Authors:  Slawik Tereschenko
//													  Vlad Remizov
//********************************************************************************************
// TestSW.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "TestSW.h"
#include "TestSWDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestSWApp

BEGIN_MESSAGE_MAP(CTestSWApp, CWinApp)
	//{{AFX_MSG_MAP(CTestSWApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestSWApp construction

CTestSWApp::CTestSWApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTestSWApp object

CTestSWApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CTestSWApp initialization

BOOL CTestSWApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	CTestSWDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

int CTestSWApp::ExitInstance() 
{
	return CWinApp::ExitInstance();
}
