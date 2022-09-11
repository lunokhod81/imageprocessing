

//Image.h

#ifndef _CIMAGE_
#define  _CIMAGE_


#include "Store.h"
#include "FloatImage.h"


class CImage 
{

	

public :
	//Construction  &  Destruction
	CImage();
	CImage(Store *pStore);
	CImage(CImage& CI);
	CImage(UINT newWidth,UINT NewHeight,UINT newDepth);	
	virtual ~CImage();

	Store *Image;
	//One and the only member
private:
	

	
public:
	//Access to members of the inside object
	
	UINT Width(){return Image->Width;}	
	UINT Height(){return Image->Height;}
	UINT Depth(){return Image->Depth;}
	CString GetFileName(){return Image->FileName;}
	
	

public:
	//Image manipulations,like size, position


	//Image Size

	int ChangeSize(const UINT NewWidth,const UINT NewHeight);
	void ChangeHeight(const UINT NewHeight);
	void ChangeWidth(const UINT NewWidth);
	
	void ChangeHeightUsingFourier(UINT NewHeight,UINT KernelType,float SmoothingAmount);
	void ChangeWidthUsingFourier(UINT newWidth,UINT KernelType,float SmoothingAmount);
	void ChangeSizeUsingFourier(UINT newWidth,UINT NewHeight,UINT KernelType,float SmoothingAmount,float StepOvershoot);	

	void ReduceSizeByIntFactors(const UINT nx,const UINT ny);
	void EnlargeSizeByIntFactors(const UINT nx,const UINT ny);

	//Image Transform
	double Aspect();
	
	int Rotate(double alpha);
	void Offset(const int xOffset,const int yOffset);
	void MirrorX();
	void MirrorY();
	void Rotate90CCW();
	void Rotate90CW();


	// Clipping
	int GetClip(CImage &ImageClp,int XL,int YL,UINT WIDTH,UINT HEIGHT);
	void SetClip(CImage& ImageClp, int const XL, const int YL, const UINT WIDTH, const UINT HEIGHT,const float factor);
	void AddClip(CImage& ImageClp,const int XL,const int YL,const UINT WIDTH,const UINT HEIGHT,const float factor);


	//Painting functions
			//Pixel Level		
	rgb GetPixel(const UINT X,const UINT Y)	{return Image->GetPixel(X,Y);}
	rgb GetPixelSafe(UINT X,UINT Y);
	void SetPixel(UINT X,UINT Y,rgb color){Image->SetPixel(X,Y,color);}
	rgb GetPixelInWndCoordinates(UINT X, UINT Y){return Image->GetPixel(X,Image->Height-Y);}
	rgb GetPixelApproximate(double X,double Y);
	void SetPixelInWndCoordinates(UINT X,UINT Y,rgb color){Image->SetPixel(X,Image->Height-Y,color);}
	rgb GetPixelApproximateByY(UINT X,double Y);
	rgb GetPixelApproximateByX(double X,UINT Y);

		//Pixel Alpha Level
	void SetPixelAlpha(UINT X,UINT Y,rgba color){ Image->SetPixelAlpha(X,Y,color);}
	rgba GetPixelAlpha(UINT X,UINT Y){ return Image->GetPixelAlpha(X,Y);}
	void SetAlpha(UINT X,UINT Y,unsigned char alpha){ Image->SetAlpha(X,Y,alpha);}
	unsigned char GetAlpha(UINT X,UINT Y){ return Image->GetAlpha(X,Y);}

	//Region Level
	void AddPixel(UINT X,UINT Y,rgb color,double factor);
	void AddRegion(const int XL,const int YL,const UINT WIDTH,const UINT HEIGHT,const rgb color,const float factor);	
	void FillRegion(int XL,int YL,UINT Width,UINT Height,rgb color,const float factor);	
	void Fill(rgb color);	

	//Color Transform
	void ConvertToMonochrome();
	void ConvertToBW();
	void Invert();
	
		
	//Operators and comparison
	BOOL SameSize(CImage &ImageToCompare);
	BOOL HasAlpha(){return Image->HasAlpha();}
	CImage& operator=(CImage& CI);	
	

public:	
	//Storing, loading 

	int ReadBMPFile(CString FileName){return Image->ReadBMPFile(FileName);}
	int SaveBMPFile(CString FileName){return Image->SaveBMPFile(FileName);}
	

	//Allocation
private:
	int Allocate(UINT Width,UINT Height,UINT Depth);	


public:
	void AddPixel(UINT X,UINT Y,rgba color);
	void SubstractPixel(UINT X, UINT Y, rgb color,double factor);
	void AddAlphaLayer(unsigned char alpha);
	int DisplayRect(CDC *pDC,CPoint Dest,CRect RectToUpdate)
	{return Image->DisplayRect(pDC,Dest,RectToUpdate);}


	void CompositePixel(UINT X,UINT Y,rgba color)
	{Image->CompositePixel(X,Y,color);}
	void SetAlphaValue(unsigned char alpha);
	rgb GetAvarageColorInRect(const int XL,const int YL,const UINT WIDTH,const UINT HEIGHT);
	void RotateFast(double alpha);
	int LoadAlphaLayer(CImage &AlphaImage);
	
	//Displaying in CDC

	int Display(CDC *pDC,int xOffset,int yOffset,int width,int height);

	
	

	


};

#endif

