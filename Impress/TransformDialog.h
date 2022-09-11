#if !defined(AFX_TRANSFORMDIALOG_H__86F14262_268D_11D5_B4FE_87A931FD7B07__INCLUDED_)
#define AFX_TRANSFORMDIALOG_H__86F14262_268D_11D5_B4FE_87A931FD7B07__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TransformDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTransformDialog dialog

class CTransformDialog : public CDialog
{
// Construction
public:
	void SetProgress(int Percent);
	void SetText(const char *Text);
	CTransformDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTransformDialog)
	enum { IDD = IDD_TRANSFORMDIALOG };
	CProgressCtrl	m_Progress;
	CString	m_Text;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransformDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTransformDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRANSFORMDIALOG_H__86F14262_268D_11D5_B4FE_87A931FD7B07__INCLUDED_)
