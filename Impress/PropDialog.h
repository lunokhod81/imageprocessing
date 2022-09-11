#if !defined(AFX_PROPDIALOG_H__6CE2C1FF_3ADF_4A22_AD6F_AD80C343C639__INCLUDED_)
#define AFX_PROPDIALOG_H__6CE2C1FF_3ADF_4A22_AD6F_AD80C343C639__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PropDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPropDialog dialog

class CPropDialog : public CDialog
{
// Construction
public:
	void UpdateDatas(CString str1,CString str2,UINT a,UINT b);
	CPropDialog(CWnd* pParent = NULL);   // standard constructor
	CPropDialog(CWnd* pParent = NULL,CString s1="",CString s2="",UINT a=0,UINT b=0); 

// Dialog Data
	//{{AFX_DATA(CPropDialog)
	enum { IDD = IDD_PROPDIALOG };
	UINT	m_a;
	UINT	m_b;
	CStatic stat1;
	CStatic stat2;
	CString str1;
	CString str2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPropDialog)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPDIALOG_H__6CE2C1FF_3ADF_4A22_AD6F_AD80C343C639__INCLUDED_)
