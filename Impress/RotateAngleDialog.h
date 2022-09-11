#if !defined(AFX_ROTATEANGLEDIALOG_H__16813BC7_68EF_4BF4_8E4B_F1FC5D296684__INCLUDED_)
#define AFX_ROTATEANGLEDIALOG_H__16813BC7_68EF_4BF4_8E4B_F1FC5D296684__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RotateAngleDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRotateAngleDialog dialog

class CRotateAngleDialog : public CDialog
{
// Construction
public:
	CRotateAngleDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRotateAngleDialog)
	enum { IDD = IDD_DIALOG2 };
	double	m_angle;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRotateAngleDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRotateAngleDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROTATEANGLEDIALOG_H__16813BC7_68EF_4BF4_8E4B_F1FC5D296684__INCLUDED_)
