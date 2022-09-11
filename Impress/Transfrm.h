// Transfrm.h: interface for the CTransform class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRANSFRM_H__86F14261_268D_11D5_B4FE_87A931FD7B07__INCLUDED_)
#define AFX_TRANSFRM_H__86F14261_268D_11D5_B4FE_87A931FD7B07__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTransformDialog;

class CTransform  
{
public:
	void SetProgress(int Percent);
	void SetText(const char *Text);
	void EndTransform();
	void StartTransform();
	CTransform();
	virtual ~CTransform();
	CStatusBar	*StatusBar;
private:
	CTransformDialog	*TD;
	clock_t	time1, time2;
};

#endif // !defined(AFX_TRANSFRM_H__86F14261_268D_11D5_B4FE_87A931FD7B07__INCLUDED_)
