#if !defined(AFX_FOURIERTRANSFORMDIALOG_H__F2D21957_572D_44B4_B4E0_989D79552FAD__INCLUDED_)
#define AFX_FOURIERTRANSFORMDIALOG_H__F2D21957_572D_44B4_B4E0_989D79552FAD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FourierTransformDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFourierTransformDialog dialog

class CFourierTransformDialog : public CDialog
{
// Construction
public:
	CFourierTransformDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFourierTransformDialog)
	enum { IDD = IDD_FOURIER_TRANSFORM_DIALOG };
	UINT	m_Height;
	UINT	m_Width;
	int		m_KernelType;
	int		m_Preset;
	float	m_Smooth;
	float	m_StepOvershoot;
//	BOOL	m_KeepRatio;
	//}}AFX_DATA





// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFourierTransformDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

private:
	int bXChanged;
	int	W0, H0; // Initial width and height
	
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFourierTransformDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangePreset();
	afx_msg void OnChangeNewWidth();
	afx_msg void OnChangeNewHeight();
	afx_msg void OnKeepAspect();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FOURIERTRANSFORMDIALOG_H__F2D21957_572D_44B4_B4E0_989D79552FAD__INCLUDED_)


