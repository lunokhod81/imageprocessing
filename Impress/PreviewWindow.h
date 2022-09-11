
#include "Image.h"
#include "ImpressDoc.h"
#include "ImpressView.h"


#if !defined(AFX_PREVIEWWINDOW_H__A806F4A5_8C0C_4E74_BF89_A236ACCADCE2__INCLUDED_)
#define AFX_PREVIEWWINDOW_H__A806F4A5_8C0C_4E74_BF89_A236ACCADCE2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PreviewWindow.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPreviewWindow frame



class CPreviewWindow : public CWnd
{
	DECLARE_DYNCREATE(CPreviewWindow)
private:
		           // protected constructor used by dynamic creation

// Attributes
public:
	CImage *pic;



// Operations
public:


	CPreviewWindow();
	~CPreviewWindow();


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPreviewWindow)
	public:
	//}}AFX_VIRTUAL

// Implementation
protected:


	// Generated message map functions
	//{{AFX_MSG(CPreviewWindow)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PREVIEWWINDOW_H__A806F4A5_8C0C_4E74_BF89_A236ACCADCE2__INCLUDED_)
