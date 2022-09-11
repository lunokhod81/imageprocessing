// ImagePlane.cpp: implementation of the CImagePlane class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Impress.h"
#include "ImagePlane.h"
#include "Image.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CImagePlane::CImagePlane():Data(NULL),Height(0),Width(0)
{	
	

}

CImagePlane::~CImagePlane()
{
	Free();
}

int CImagePlane::Alloc(int NewWidth, int NewHeight)
{
	Free();



	Height=NewHeight;
	Width=NewWidth;
	
	Data=new float*[Height];
	if(!Data) return -1;

	for(int i=0;i<Height;i++)
	{
		Data[i]=new float[Width];
		if(!Data[i])
		{
			for(int j=0;j<i;j++)
				delete [] Data[j];

			delete [] Data;
			return -1;
		}
	}
	return 0;

}

void CImagePlane::Free()
{
	if(!Data)
		return;

	for(int i=0;i<Height;i++)	
		delete [] Data[i];
		
	

	delete [] Data;


}

CImagePlane::CImagePlane(CImagePlane &IP)
{
	Free();
	Alloc(IP.Width,IP.Height);
	for(int i=0;i<Height;i++)
		memcpy(Data[i],IP.Data[i],Width*sizeof(float));




}

CImagePlane& CImagePlane::operator =(CImagePlane &IP)
{
	Free();
	Alloc(IP.Width,IP.Height);
	for(int i=0;i<Height;i++)
		memcpy(Data[i],IP.Data[i],Width*sizeof(float));

	return *this;

}

CImagePlane::CFloatImage(CImage &Image)
{

}

int CImagePlane::LoadImage(CImage &Image)
{
	Alloc(Image.Width(),Image.Height());
	
	for(int x=0;x<Image.Width();x++)
		for(int y=0;y<Image.Height();y++)
			Data[y][x]=(float)Image.GetPixel(x,y).Grey();

	return 0;



}

void CImagePlane::Normalize255()
{
		for(int x=0;x<Width;x++)
			for(int y=0;y<Height;y++)
				Data[y][x]/=255;

}
