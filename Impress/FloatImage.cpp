// FloatImage.cpp: implementation of the CFloatImage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Impress.h"
#include "FloatImage.h"
#

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFloatImage::CFloatImage()
{

}

CFloatImage::~CFloatImage()
{

}

int CFloatImage::LoadImage(CImage &Image)
{
	
	RPlane.Alloc(Image.Width(),Image.Height());
	GPlane.Alloc(Image.Width(),Image.Height());
	BPlane.Alloc(Image.Width(),Image.Height());


	for(int x=0;x<Image.Width();x++)
		for(int y=0;y<Image.Height();y++)
			SetPixel(x,y,Image.GetPixel(x,y));

	return 0;


}

void CFloatImage::SetPixel(int x, int y, rgb color)
{
	ASSERT(x>=0 && x<RPlane.Width && y>=0 && y<RPlane.Height);

	RPlane.Data[y][x]=(float)color.r;
	GPlane.Data[y][x]=(float)color.g;
	BPlane.Data[y][x]=(float)color.b;
}

CFloatImage::CFloatImage(CImage &Image)
{
	LoadImage(Image);
	
}

rgb CFloatImage::GetPixel(int x, int y)
{
	return rgb(RPlane.Data[y][x]*255.0f,GPlane.Data[y][x]*255.0f,BPlane.Data[y][x]*255.0f);

}

void CFloatImage::Normalize255()
{
	RPlane.Normalize255();
	GPlane.Normalize255();
	BPlane.Normalize255();

}
