// PreviewWindow.cpp : implementation file
//

#include "stdafx.h"
#include "Impress.h"
#include "PreviewWindow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPreviewWindow

IMPLEMENT_DYNCREATE(CPreviewWindow, CFrameWnd)

CPreviewWindow::CPreviewWindow()
{
	


}

CPreviewWindow::~CPreviewWindow()
{
 

}


BEGIN_MESSAGE_MAP(CPreviewWindow, CWnd)
	//{{AFX_MSG_MAP(CPreviewWindow)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPreviewWindow message handlers





void CPreviewWindow::OnPaint() 
{
	CPaintDC dc(this); // device context for painting


	int xOffset=GetScrollPos(SB_HORZ);
	int yOffset=-GetScrollPos(SB_VERT);
	if(pic)
		pic->Display(&dc,xOffset,yOffset,-1,-1);
	else
	{
		CRect Client;
		GetClientRect(&Client);
		CBrush Brush(RGB(0,255,0));

		dc.FillRect(&Client,&Brush);
	}




	
}
















