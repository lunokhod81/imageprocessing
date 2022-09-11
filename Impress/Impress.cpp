// Impress.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Impress.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "ImpressDoc.h"
#include "ImpressView.h"


#include "PropDialog.h"








#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImpressApp

BEGIN_MESSAGE_MAP(CImpressApp, CWinApp)
//{{AFX_MSG_MAP(CImpressApp)
ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
ON_COMMAND(ID_IMAGE_DUPLICATE, OnImageDuplicate)
	//}}AFX_MSG_MAP
// Standard file based document commands
ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
// Standard print setup command
ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImpressApp construction






CImpressApp::CImpressApp()
{	
	
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CImpressApp object



CImpressApp theApp;




/////////////////////////////////////////////////////////////////////////////
// CImpressApp initialization

BOOL CImpressApp::InitInstance()
{
	

	
	
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.
	
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
	
	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	
	LoadStdProfileSettings();  // Load standard INI file options (including MRU)
	
	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.
	
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_IMPRESTYPE,
		RUNTIME_CLASS(CImpressDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CImpressView));
	AddDocTemplate(pDocTemplate);



	AfxEnableControlContainer();
	
	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;
	
	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	
	cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;
	
	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	
	// The main window has been initialized, so show and update it.
	//pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->ShowWindow(SW_MAXIMIZE);
	pMainFrame->UpdateWindow();

	
	
	
	
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	
	// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA
	
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
//{{AFX_MSG_MAP(CAboutDlg)
// No message handlers
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CImpressApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CImpressApp message handlers


void CImpressApp::OnImageDuplicate() 
{	
	
	// GetActiveDocument
	
	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)m_pMainWnd;
	CMDIChildWnd *pChild = (CMDIChildWnd *) pFrame->GetActiveFrame();	
	CImpressView *pView =  (CImpressView *) pChild->GetActiveView();	
	
	CImpressDoc *ActiveDoc=(CImpressDoc*)(pView->GetDocument());
	CString ActiveDocumentText=ActiveDoc->GetTitle();	
	//Add to the Image Template
	AddNewImageDocument(&(ActiveDoc->pic),ActiveDocumentText+" Copy");		
}


void CImpressApp::AddNewImageDocument(CImage *pic,CString Title)
{
	
	
	POSITION pos = GetFirstDocTemplatePosition( );
	CString DocString;
	CDocTemplate* doctemplate;
	while(pos)
	{
		doctemplate =GetNextDocTemplate(pos );	
		doctemplate->GetDocString(DocString,CDocTemplate::docName);
		if(DocString=="Impres")break;
	}
	
	
	CImpressDoc *pdoc=(CImpressDoc*)(doctemplate->CreateNewDocument());
	ASSERT_VALID(pdoc);
	
	
	pdoc->pic=*pic;
	
	
	CFrameWnd* newFrame=doctemplate->CreateNewFrame(pdoc,(CFrameWnd*)m_pMainWnd);
	newFrame->SetWindowText(Title);	
	pdoc->SetTitle(Title);		
	pdoc->statusbar = &(((CMainFrame*)m_pMainWnd)->m_wndStatusBar);
	

	((CMDIFrameWnd*)m_pMainWnd)->MDIActivate(newFrame);	
	doctemplate->InitialUpdateFrame(newFrame,pdoc,TRUE);	
	pdoc->UpdateAllViews(NULL);	
}







	




