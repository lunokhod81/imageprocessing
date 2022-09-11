// FractalDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Impress.h"
#include "FractalDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFractalDialog dialog


CFractalDialog::CFractalDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CFractalDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFractalDialog)
	m_eps = 0.001f;
	m_P1 = 1.0f;
	//}}AFX_DATA_INIT
}


void CFractalDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFractalDialog)
	DDX_Text(pDX, IDC_EPS, m_eps);
	DDX_Text(pDX, IDC_P1, m_P1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFractalDialog, CDialog)
	//{{AFX_MSG_MAP(CFractalDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFractalDialog message handlers
