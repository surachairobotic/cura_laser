//						Raylase AG
//				Test sample for SP-ICE
//											Authors:  Slawik Tereschenko
//													  Vlad Remizov
//********************************************************************************************
// TestSWDlg.cpp : implementation file
//
#include "stdafx.h"
#include "TestSW.h"
#include "TestSWDlg.h"
//1*************
#include <windows.h>
#include "SPIC_Export.h"
//1*************
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


bool bNonStop = false;

CTestSWDlg::CTestSWDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestSWDlg::IDD, pParent)
{
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
//1*****************************************************************************	
	// Initialisation of global variables
//1*****************************************************************************
}

void CTestSWDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CTestSWDlg)
	DDX_Text( pDX, IDC_X, m_XVal);
	DDX_Text( pDX, IDC_Y, m_YVal);

	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestSWDlg, CDialog)
	//{{AFX_MSG_MAP(CTestSWDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, OnInitCard)
	ON_BN_CLICKED(IDC_GET_SN, OnGetSn)
	ON_BN_CLICKED(IDC_GET_VERSION, OnGetVersion)
	ON_BN_CLICKED(IDC_SET_MODE, OnSetMode)
	ON_BN_CLICKED(IDC_SET_START_LIST, OnSetStartList)
	ON_BN_CLICKED(IDC_SET_DELAYS, OnSetDelays)
	ON_BN_CLICKED(IDC_SET_SPEED, OnSetSpeed)
	ON_BN_CLICKED(IDC_BUTTON_JUMP_ABS, OnJumpAbs)
	ON_BN_CLICKED(IDC_KVADRAT, OnKvadrat)
	ON_BN_CLICKED(IDC_SET_END_OF_LIST, OnSetEndOfList)
	ON_BN_CLICKED(IDC_EXECUTE_LIST, OnExecuteList)
	ON_BN_CLICKED(IDC_STOP_EXECUTION, OnStopExecution)

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestSWDlg message handlers

BOOL CTestSWDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	this->m_XVal = 0;
	this->m_YVal = 0;

	this->UpdateData(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestSWDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else{	CDialog::OnPaint();	}
}
// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTestSWDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
//1*******************************************************************************************
///////////////////////////// BUTTONS  /////////////////////////////**************************
BOOL bInitCard = FALSE;
BOOL bSetMode = FALSE;

//char * fname = "C:\\Program Files (x86)\\RAYLASE\\SP-ICE\\SampleCode\\VisualC\\C200_15.gcd";
char * fname = "E:\\Laser software\\Raylase\\TSL-355-90-163-D10-B_MS-10_LR25,0.gcd";

void CTestSWDlg::OnInitCard() 
{
	bInitCard = (Init_Scan_Card_Ex(1) == 0);
	if (bInitCard) ::MessageBox(0, "Init Card TRUE...", 0, MB_OK);
	else ::MessageBox(0, "Init Card FALSE...", 0, MB_OK);
} 

void CTestSWDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}


void CTestSWDlg::OnSetMode() 
{
	unsigned short usMode = 0x0410;
	
	char buff[100];
	sprintf_s(buff, 100, "%d", usMode);
	::MessageBox(0, buff, 0, MB_OK);

	if(bInitCard)
	{
		bSetMode = Set_Mode(usMode);

		if (bSetMode) {
			BOOL isOK = Load_Cor(fname);

			if (isOK); //
			else ::MessageBox(0, "FALSE Loading correction file...", 0, MB_OK);
		}
		else 
			::MessageBox(0, "SetMode FALSE...", 0, MB_OK);
	}
	else 
		::MessageBox(0, "Card is not initialized..", 0, MB_OK);
} 

void CTestSWDlg::OnSetEndOfList() 
{
	if(bInitCard && bSetMode)
	{
		BOOL isOK = Set_End_Of_List();
		if (isOK){
			//
		} else 
			::MessageBox(0, "Cannot make Set_End_Of_List", 0, MB_OK);
	}
	else ::MessageBox(0, "Card is not initialised or mode is not set", 0, MB_OK);
}

void CTestSWDlg::OnSetStartList() 
{
	if(bInitCard && bSetMode)
	{
		BOOL isOK = Set_Start_List_1();
		if (isOK){
				//
		} else 
			::MessageBox(0, "Cannot make Set_Start_List_1", 0, MB_OK);
	}
	else ::MessageBox(0, "Card is not initialised or mode is not set", 0, MB_OK);
}

void CTestSWDlg::OnExecuteList() 
{
	if(bInitCard && bSetMode)
	{
		BOOL isOK = Execute_List_1();
		if (isOK){
				//
		} else 
			::MessageBox(0, "Cannot make Execute_List_1", 0, MB_OK);
	}
	else ::MessageBox(0, "Card is not initialised or mode is not set", 0, MB_OK);
}

void CTestSWDlg::OnJumpAbs() 
{
	this->UpdateData(TRUE);
	
	Jump_Abs(this->m_XVal,this->m_YVal);
}


void CTestSWDlg::OnSetDelays() 
{
	if(bInitCard && bSetMode)
	{
		BOOL isOK = Set_Delays(	60, 100,	
								100, 100,		
								100, 100,
								100, 50, 0);
	}
	else ::MessageBox(0, "Card is not initialised or mode is not set", 0, MB_OK);
}

void CTestSWDlg::OnSetSpeed() 
{
	if(bInitCard && bSetMode)
	{
		BOOL isOK = Set_Speed(500,150);
	}
	else ::MessageBox(0, "Card is not initialised or mode is not set", 0, MB_OK);
}

void CTestSWDlg::OnKvadrat() 
{
	int i=0;
	BOOL isOK;

	this->UpdateData(TRUE);

	char buf[100];
	sprintf(buf, "X,Y : %d,%d", this->m_XVal, this->m_YVal);
	::MessageBox(0, buf, " ", MB_OK);
	isOK = PolA_Abs(this->m_XVal, this->m_YVal + 10000);
	isOK = PolB_Abs(this->m_XVal+10000, this->m_YVal +10000);
	isOK = PolB_Abs(this->m_XVal+10000, this->m_YVal);
	isOK = PolC_Abs(this->m_XVal, this->m_YVal);
}


void CTestSWDlg::OnStopExecution() 
{
	BOOL isOK = Stop_Execution(); 
}


void CTestSWDlg::OnGetSn() 
{
	if(bInitCard)
	{
		UINT iSN = Get_Ident_Ex();
		if (iSN){ 
			char buf[100];
			sprintf(buf, "SN = %d (0x%08X hex)", iSN, iSN);
			::MessageBox(0, buf, "Serial number is:", MB_OK);
		} else 
			::MessageBox(0, "Serial number is not set", 0, MB_OK);
	}
	else ::MessageBox(0, "Card is not initialised !", 0, MB_OK);
}


void CTestSWDlg::OnGetVersion() 
{
	if(bInitCard)
	{
		UINT Ver_RTB = Get_Version();
		UINT Ver_DLL = Get_DLL_Version();
		
		char buf[100];
		sprintf(buf, "DLL Ver = %d, RTB Ver = %d", Ver_DLL, Ver_RTB);
		::MessageBox(0, buf, "Version Info", MB_OK);

	}
	else ::MessageBox(0, "Card is not initialised !", 0, MB_OK);
}


