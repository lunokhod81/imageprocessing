// RotateAngleDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Impress.h"
#include "RotateAngleDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRotateAngleDialog dialog


CRotateAngleDialog::CRotateAngleDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CRotateAngleDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRotateAngleDialog)
	m_angle = 0.0;
	//}}AFX_DATA_INIT
}


void CRotateAngleDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRotateAngleDialog)
	DDX_Text(pDX, IDC_ANGLE, m_angle);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRotateAngleDialog, CDialog)
	//{{AFX_MSG_MAP(CRotateAngleDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRotateAngleDialog message handlers
