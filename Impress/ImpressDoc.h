// ImpressDoc.h : interface of the CImpressDoc class
//
/////////////////////////////////////////////////////////////////////////////



#if !defined(AFX_IMPRESSDOC_H__6B54A891_A12B_4898_A45B_C30A5732DFF7__INCLUDED_)
#define AFX_IMPRESSDOC_H__6B54A891_A12B_4898_A45B_C30A5732DFF7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



#include "Image.h"



class CImpressDoc : public CDocument
{

protected: // create from serialization only

	

// Attributes
public:
	CImpressDoc(UINT X,UINT Y);
	CImpressDoc();
	
	DECLARE_DYNCREATE(CImpressDoc)


// Operations
public:
		

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImpressDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	float CntPColor(float x, float y, float P1, int maxit=100, int num=70, float eps=0.001);
	void Fetch();
	CRect GetImageRect();
	void Hold();
	


	CImage pic;
	Store Holded;
	CImpressDoc &operator=(CImpressDoc& CD);
	CStatusBar *statusbar;

	virtual ~CImpressDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CImpressDoc)
	afx_msg void OnImageImagesize();
	afx_msg void OnImageTransformFlipvertical();
	afx_msg void OnImageTransformFliphorizontal();
	afx_msg void OnImageTransformRotateRotate90ccw();
	afx_msg void OnImageTransformRotateRotate90cw();
	afx_msg void OnImageTransformRotateRotatenumeric();
	afx_msg void OnImageGrayscale();
	afx_msg void OnImageMonochrome();
	afx_msg void OnImageTransformOffset();
	afx_msg void OnImageModeInvert();
	afx_msg void OnImageChangeimagesizeChangeusingfourier();
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
	afx_msg void OnImageGeneratefractal();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMPRESSDOC_H__6B54A891_A12B_4898_A45B_C30A5732DFF7__INCLUDED_)
