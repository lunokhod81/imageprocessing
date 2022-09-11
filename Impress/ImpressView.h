// ImpressView.h : interface of the CImpressView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMPRESSVIEW_H__68C6A7C9_3016_4AE8_B616_36D24E89D5C0__INCLUDED_)
#define AFX_IMPRESSVIEW_H__68C6A7C9_3016_4AE8_B616_36D24E89D5C0__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



class CImpressView : public CScrollView
{
protected: // create from serialization only
	CImpressView();
	DECLARE_DYNCREATE(CImpressView)

// Attributes
public:
	CImpressDoc* GetDocument();
	CRect ImageRect;
	CRect UpdateRect;
	

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImpressView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	int state;


	virtual ~CImpressView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CImpressView)
	afx_msg void OnImageImageinfo();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ImpressView.cpp
inline CImpressDoc* CImpressView::GetDocument()
   { return (CImpressDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMPRESSVIEW_H__68C6A7C9_3016_4AE8_B616_36D24E89D5C0__INCLUDED_)
