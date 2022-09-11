// FourierTransformDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Impress.h"
#include "FourierTransformDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFourierTransformDialog dialog


CFourierTransformDialog::CFourierTransformDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CFourierTransformDialog::IDD, pParent),
	bXChanged(1),
	W0(0),
	H0(0)
{
	//{{AFX_DATA_INIT(CFourierTransformDialog)
	m_Height = 0;
	m_Width = 0;
	m_KernelType = -1;
	m_Preset = 0;
	m_Smooth = 0.0f;
	m_StepOvershoot = 0.0f;
	//}}AFX_DATA_INIT
}


void CFourierTransformDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFourierTransformDialog)
	DDX_Text(pDX, IDC_NEW_HEIGHT, m_Height);
	DDV_MinMaxUInt(pDX, m_Height, 1, 100000);
	DDX_Text(pDX, IDC_NEW_WIDTH, m_Width);
	DDV_MinMaxUInt(pDX, m_Width, 1, 100000);
	DDX_Radio(pDX, IDC_KERNEL_TYPE, m_KernelType);
	DDX_CBIndex(pDX, IDC_PREDEFINED, m_Preset);
	DDX_Text(pDX, IDC_NEW_SMOOTH, m_Smooth);
	DDX_Text(pDX, IDC_STEPOVERSHOOT, m_StepOvershoot);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFourierTransformDialog, CDialog)
	//{{AFX_MSG_MAP(CFourierTransformDialog)
	ON_CBN_SELCHANGE(IDC_PREDEFINED, OnSelchangePreset)
	ON_EN_CHANGE(IDC_NEW_WIDTH, OnChangeNewWidth)
	ON_EN_CHANGE(IDC_NEW_HEIGHT, OnChangeNewHeight)
	ON_BN_CLICKED(IDC_KEEPASPECT, OnKeepAspect)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFourierTransformDialog message handlers



BOOL CFourierTransformDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

	W0 = m_Width;
	H0 = m_Height;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CFourierTransformDialog::OnSelchangePreset() 
{
	UpdateData(TRUE);
	switch (m_Preset) {
	case 0 : {
		m_Smooth = 0.95;
		m_StepOvershoot = 12;
		m_KernelType = 1;
		break;
			 }
	case 1 : {
		m_Smooth = 0.87;
		m_StepOvershoot = 12;
		m_KernelType = 1;
		break;
			 }
	case 2 : {
		m_Smooth = 0.95;
		m_StepOvershoot = 5;
		m_KernelType = 0;
		break;
			 }
	case 3 : {
		m_Smooth = 1;
		m_StepOvershoot = 6.7;
		m_KernelType = 0;
		break;
			 }
	case 4 : {
		m_Smooth = 1.5;
		m_StepOvershoot = 12;
		m_KernelType = 1;
		break;
			 }
	case 5 : {
		m_Smooth = 1;
		m_StepOvershoot = 11;
		m_KernelType = 1;
		break;
			 }
	}
	UpdateData(FALSE);
}



void CFourierTransformDialog::OnChangeNewWidth() 
{	
	bXChanged = 1;
}

void CFourierTransformDialog::OnChangeNewHeight() 
{
	bXChanged = 0;
}


void CFourierTransformDialog::OnKeepAspect() 
{
	UpdateData(TRUE);
	if (bXChanged) {
		if (m_Width<=0) m_Width = 1;
		m_Height = (int)(m_Width * (float)H0/W0 + 0.5);
		if (m_Height<=0) m_Height = 1;
	}
	else {
		if (m_Height<=0) m_Height = 1;
		m_Width = (int)(m_Height * (float)W0/H0 + 0.5);
		if (m_Width<=0) m_Width = 1;
	}
	UpdateData(FALSE);
}
