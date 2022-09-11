// TransformDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Impress.h"
#include "TransformDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTransformDialog dialog


CTransformDialog::CTransformDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CTransformDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTransformDialog)
	m_Text = _T("");
	//}}AFX_DATA_INIT
}


void CTransformDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTransformDialog)
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);
	DDX_Text(pDX, IDC_STATIC1, m_Text);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTransformDialog, CDialog)
	//{{AFX_MSG_MAP(CTransformDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransformDialog message handlers

void CTransformDialog::SetText(const char *Text)
{
	m_Text = CString(Text);
	UpdateData(FALSE);
	UpdateWindow();
}

void CTransformDialog::SetProgress(int Percent)
{
	m_Progress.SetPos(Percent);
	UpdateData(FALSE);
	UpdateWindow();
}
