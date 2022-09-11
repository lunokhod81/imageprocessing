// FloatImage.h: interface for the CFloatImage class.
//
//////////////////////////////////////////////////////////////////////
#include "ImagePlane.h"
#include "Image.h"
#include "Store.h"	// Added by ClassView


#if !defined(AFX_FLOATIMAGE_H__B86FAE04_A3FB_4B9D_9086_578A33ED7F41__INCLUDED_)
#define AFX_FLOATIMAGE_H__B86FAE04_A3FB_4B9D_9086_578A33ED7F41__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFloatImage  
{
public:
	void Normalize255();
	rgb GetPixel(int x,int y);
	CFloatImage(CImage &Image);
	void SetPixel(int x,int y,rgb color);
	int LoadImage(CImage &Image);
	CImagePlane RPlane,GPlane,BPlane;	
	CFloatImage();
	virtual ~CFloatImage();
	

};

#endif // !defined(AFX_FLOATIMAGE_H__B86FAE04_A3FB_4B9D_9086_578A33ED7F41__INCLUDED_)
