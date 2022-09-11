// ImagePlane.h: interface for the CImagePlane class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGEPLANE_H__5161B8A1_4BC5_4D26_8BCE_AA0EBCA048BD__INCLUDED_)
#define AFX_IMAGEPLANE_H__5161B8A1_4BC5_4D26_8BCE_AA0EBCA048BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CImagePlane  
{
public:
	void Normalize255();
	int LoadImage(CImage &Image);
	CFloatImage(CImage &Image);
	CImagePlane(CImagePlane &IP);
	void Free();
	int Alloc(int NewWidth,int NewHeight);
	float **Data;
	int Width,Height;
	CImagePlane();
	CImagePlane& operator =(CImagePlane &IP);
	virtual ~CImagePlane();

};

#endif // !defined(AFX_IMAGEPLANE_H__5161B8A1_4BC5_4D26_8BCE_AA0EBCA048BD__INCLUDED_)
