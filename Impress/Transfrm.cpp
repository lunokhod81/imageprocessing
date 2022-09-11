// Transfrm.cpp: implementation of the CTransform class.
//
//////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "Impress.h"
#include "Transfrm.h"

#include "TransformDialog.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTransform::CTransform()
{
	StatusBar = NULL;
}

CTransform::~CTransform()
{

}

void CTransform::StartTransform()
{
	TD = new CTransformDialog(NULL/*GetMainWnd()*/);
	TD->Create(IDD_TRANSFORMDIALOG);
	TD->ShowWindow(SW_SHOW);
	TD->UpdateWindow();
	TD->m_Text = CString("Starting transform...");
	TD->m_Progress.SetRange(0,100);
	TD->m_Progress.SetPos(0);
	time1 = clock();
}

#define S_TRANSFORMCOMPLETE	"Transform completed in %d.%d seconds"

void CTransform::EndTransform()
{
	// Destroy dialog...
	TD->DestroyWindow();
	delete TD;
	// Calculate elapsed time...
	time2 = clock() - time1;
	char str[100];
	int	Sec, MSec;
	Sec = time2/CLK_TCK;
	MSec = time2 - Sec*1000;
	sprintf(str, S_TRANSFORMCOMPLETE, Sec, MSec);
	if (StatusBar) StatusBar->SetPaneText(0, str, TRUE);
}

void CTransform::SetText(const char *Text)
{
	TD->SetText(Text);
}

void CTransform::SetProgress(int Percent)
{
	TD->SetProgress(Percent);
}

