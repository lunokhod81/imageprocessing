// Impress.h : main header file for the IMPRESS application
//

#if !defined(AFX_IMPRESS_H__E3567F83_09B9_4DB4_AFE0_89531647F192__INCLUDED_)
#define AFX_IMPRESS_H__E3567F83_09B9_4DB4_AFE0_89531647F192__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols



#include "Image.h"	// Added by ClassView
/////////////////////////////////////////////////////////////////////////////
// CImpressApp:
// See Impress.cpp for the implementation of this class
//



int NumberOfBrushDocs();


class CImpressApp : public CWinApp
{
public:
	void AddNewImageDocument(CImage *pic,CString Title);

//	CCompressDialog *CompDlg;


	

	
	CImpressApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImpressApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CImpressApp)
	afx_msg void OnAppAbout();
	afx_msg void OnImageDuplicate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMPRESS_H__E3567F83_09B9_4DB4_AFE0_89531647F192__INCLUDED_)
