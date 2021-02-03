// TestSWDlg.h : header file
//

#if !defined(AFX_TESTSWDLG_H__B3001466_CA01_11D5_A00E_00C0DF019CE8__INCLUDED_)
#define AFX_TESTSWDLG_H__B3001466_CA01_11D5_A00E_00C0DF019CE8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/////////////////////////////////////////////////////////////////////////////
// CTestSWDlg dialog

class CTestSWDlg : public CDialog
{
// Construction
//1*****************************************************************************
public:
	//Declaration variabls with TYP
//1*****************************************************************************

	CTestSWDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestSWDlg)
	enum { IDD = IDD_TESTSW_DIALOG };
	short m_XVal;
	short m_YVal;

	BOOL	m_bBit0;
	BOOL	m_bBit1;
	BOOL	m_bBit4;
	BOOL	m_bBit5;
	BOOL	m_bBit6;
	BOOL	m_bBit10;
	BOOL	m_bBit12;

	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestSWDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestSWDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnInitCard();
	afx_msg void OnGetSn();
	afx_msg void OnGetVersion();

	afx_msg void OnSetMode();
	afx_msg void OnSetStartList();
	afx_msg void OnSetDelays();
	afx_msg void OnSetSpeed();
	afx_msg void OnJumpAbs();
	afx_msg void OnKvadrat();
	afx_msg void OnSetEndOfList();
	afx_msg void OnExecuteList();
	afx_msg void OnStopExecution();

	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTSWDLG_H__B3001466_CA01_11D5_A00E_00C0DF019CE8__INCLUDED_)
