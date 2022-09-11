// PropDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Impress.h"
#include "PropDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropDialog dialog


CPropDialog::CPropDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CPropDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPropDialog)
	m_a = 0;
	m_b = 0;
	//}}AFX_DATA_INIT
}

CPropDialog::CPropDialog(CWnd* pParent,CString s1,CString s2,UINT a,UINT b)
: CDialog(CPropDialog::IDD, pParent)
{
	
	//{{AFX_DATA_INIT(CPropDialog)
	m_a=a;
	m_b=b;
	//}}AFX_DATA_INIT
	str1=s1;
	str2=s2;
}


void CPropDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropDialog)
	DDX_Text(pDX, IDC_A, m_a);
	DDX_Text(pDX, IDC_B, m_b);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPropDialog, CDialog)
	//{{AFX_MSG_MAP(CPropDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropDialog message handlers



BOOL CPropDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	//ltrb
	CRect Client1(0,34,150,50);
	CPoint Pt(0,40);
	CRect Client2=Client1+Pt;
		
	

	
	stat1.Create(str1,WS_CHILD|WS_VISIBLE|SS_RIGHT,Client1,this);
	stat2.Create(str2,WS_CHILD|WS_VISIBLE|SS_RIGHT,Client2,this);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPropDialog::UpdateDatas(CString s1, CString s2, UINT a, UINT b)
{
	str1=s1;
	str2=s2;
	m_a=a;
	m_b=b;
	UpdateData(TRUE);

}
