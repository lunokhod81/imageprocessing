#if !defined(AFX_FRACTALDIALOG_H__D90F46FA_696E_4BB6_B58A_8239CE4FD4E9__INCLUDED_)
#define AFX_FRACTALDIALOG_H__D90F46FA_696E_4BB6_B58A_8239CE4FD4E9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FractalDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFractalDialog dialog

class CFractalDialog : public CDialog
{
// Construction
public:
	CFractalDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFractalDialog)
	enum { IDD = IDD_FRACTALDIALOG1 };
	float	m_eps;
	float	m_P1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFractalDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFractalDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FRACTALDIALOG_H__D90F46FA_696E_4BB6_B58A_8239CE4FD4E9__INCLUDED_)
