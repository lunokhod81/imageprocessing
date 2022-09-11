// ImpressView.cpp : implementation of the CImpressView class
//

#include "stdafx.h"
#include "Impress.h"

#include "ImpressDoc.h"
#include "ImpressView.h"
#include "Image.h"
#include "MainFrm.h"





#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImpressView

IMPLEMENT_DYNCREATE(CImpressView, CScrollView)

BEGIN_MESSAGE_MAP(CImpressView, CScrollView)
	//{{AFX_MSG_MAP(CImpressView)
	ON_COMMAND(ID_IMAGE_IMAGEINFO, OnImageImageinfo)
	ON_WM_HSCROLL()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImpressView construction/destruction

CImpressView::CImpressView()
{
	state=0;


}

CImpressView::~CImpressView()
{
}

BOOL CImpressView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.cx=150;
	cs.cy=150;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CImpressView drawing


void CImpressView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CImpressDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);


	CRect rect;
	GetParent()->GetWindowRect(rect);
	rect.bottom=rect.top+pDoc->pic.Height();
	rect.right=rect.left+pDoc->pic.Width();
	GetParent()->MoveWindow(rect,TRUE);


	CSize sizeTotal;	
	sizeTotal.cx =pDoc->pic.Width();
	sizeTotal.cy =pDoc->pic.Height();

	CSize SizePage;
	SizePage.cx=10;
	SizePage.cy=10;




	SetScrollSizes(MM_TEXT, sizeTotal,SizePage,CSize(1,1) );

	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
	
	
	
}

/////////////////////////////////////////////////////////////////////////////
// CImpressView printing

BOOL CImpressView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CImpressView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CImpressView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CImpressView diagnostics

#ifdef _DEBUG
void CImpressView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CImpressView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CImpressDoc* CImpressView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImpressDoc)));
	return (CImpressDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CImpressView message handlers





void CImpressView::OnImageImageinfo() 
{
	CImpressDoc *pdoc=GetDocument();
	ASSERT_VALID(pdoc);

	CString Info;
	Info.Format("Width=%d  Height=%d  Depth=%d",pdoc->pic.Width(),pdoc->pic.Height(),pdoc->pic.Depth());
	AfxMessageBox(Info);

	// TODO: Add your command handler code here
	
}









void CImpressView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CImpressDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);


	ImageRect=pDoc->GetImageRect();

	CSize sizeTotal;	
	sizeTotal.cx =pDoc->pic.Width();
	sizeTotal.cy =pDoc->pic.Height();

	CSize SizePage;
	SizePage.cx=10;
	SizePage.cy=10;



	SetScrollSizes(MM_TEXT, sizeTotal,SizePage,CSize(1,1) );

	SetWindowPos(NULL, 0, 0,pDoc->pic.Width(),pDoc->pic.Height(),
		SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
	
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
	Invalidate(TRUE);
	UpdateWindow();
	
	
}















void CImpressView::OnDraw(CDC* pDC)
{

	
	CImpressDoc* pDoc = GetDocument();	
	ASSERT_VALID(pDoc);
	

	
	CRect ClipRect;

	pDC->GetClipBox(&ClipRect);
	ClipRect.InflateRect(1, 1);
	
	if(ClipRect.IntersectRect(&ClipRect,&ImageRect))
		pDoc->pic.DisplayRect(pDC,ClipRect.TopLeft(),ClipRect);
		//pDoc->pic.DisplayRect(pDC,ClipRect.TopLeft(),ClipRect+GetScrollPosition());
	
		

	
	
}



void CImpressView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{	
	CScrollView::OnHScroll(nSBCode, nPos, pScrollBar);
	Invalidate(FALSE);
}







void CImpressView::OnTimer(UINT nIDEvent) 
{
	state++;

	
	CScrollView::OnTimer(nIDEvent);
}
