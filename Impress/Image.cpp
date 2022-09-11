
//Image->cpp
#include "stdafx.h"
#include "math.h"
#include "Image.h"

#include "Resource.h"
#include "MainFrm.h"
#include "Transfrm.h"
//#include "DB.h"
//#include "FFT.h"
#include "Rsmp.h"
#include "Signal.h"


#include "misc.h"

CImage::CImage():Image(new Store(51,51,24))
{
//	Image=new Store(51,51,24);
	
}


CImage::CImage(UINT NewWidth,UINT NewHeight,UINT newDepth):Image(new Store(NewWidth,NewHeight,newDepth))
{
//	Image = new Store(NewWidth,NewHeight,newDepth);
	
}


CImage::~CImage()
{
	delete Image;
	
}


CImage& CImage::operator=(CImage& CI)
{
	
	if(this==&CI) return *this;
	*Image=*(CI.Image);
	return *this;
	
}



rgb CImage::GetPixelApproximate(double X,double Y)

{
	
	if((X-(int)X==0.5) && (Y-(int)Y==0.5))
		return GetPixelSafe((int)X,(int)Y);
	
	if(X-(int)X==0.5)
		return GetPixelApproximateByX((UINT)X,(UINT)Y);
	
	if(Y-(int)Y==0.5)
		return GetPixelApproximateByY((UINT)X,(UINT)Y);
	
	
	
	
	int XC=(int)(X+0.5);
	int YC=(int)(Y+0.5);
	
	
	double Xo=(double)XC-0.5;
	double Yo=(double)YC-0.5;
	
	double x=X-Xo;
	double y=Y-Yo;
	
	double c00=(1.0-x)*(1.0-y);
	double c01=x*(1.0-y);
	double c10=y*(1.0-x);
	double c11=x*y;
	
	
	rgb pc00=GetPixelSafe(XC-1,YC-1);
	rgb pc01=GetPixelSafe(XC,YC-1);
	rgb pc10=GetPixelSafe(XC-1,YC);
	rgb pc11=GetPixelSafe(XC,YC);
	
	
	unsigned char r=(unsigned char)(c00*(double)pc00.r+(double)c01*pc01.r+c10*(double)pc10.r+c11*(double)pc11.r);
	unsigned char g=(unsigned char)(c00*(double)pc00.g+(double)c01*pc01.g+c10*(double)pc10.g+c11*(double)pc11.g);
	unsigned char b=(unsigned char)(c00*(double)pc00.b+(double)c01*pc01.b+c10*(double)pc10.b+c11*(double)pc11.b);
	
	return rgb(r,g,b);
	
	
	
}




int CImage::GetClip(CImage &ImageClp,int XL,int YL,UINT WIDTH,UINT HEIGHT)
{
	
	
	if ((ImageClp.Width()!=WIDTH) || (ImageClp.Height()!=HEIGHT)
		|| (ImageClp.Depth()!=Depth()))
		ImageClp.Allocate(WIDTH,HEIGHT,Depth());
	
	int newX,newY;
	
	for(UINT i=0;i<WIDTH;i++)
		for(UINT j=0;j<HEIGHT;j++)
		{
			newX=i+XL;newY=j+YL;
			if(newX<0 || newX>=(int)Width() || newY<0 || newY>=(int)Height())
				ImageClp.SetPixel(i,j,rgb((unsigned char)0,(unsigned char)0,(unsigned char)0));
			else			
				ImageClp.SetPixel(i,j,GetPixel(newX,newY));
			
		}
		return 1;
		
}


void CImage::MirrorY()
{
	
	Store *NewImage=new Store(Width(),Height(),Depth());
	Store *tmp;
	
	for(UINT i=0;i<Width();i++)
		for(UINT j=0;j<Height();j++)
			NewImage->SetPixel(Width()-i-1,j,GetPixel(i,j));
		
		tmp=Image;
		Image=NewImage;
		delete tmp;	
		
}


void CImage::MirrorX()
{
	
	Store *NewImage=new Store(Width(),Height(),Depth());
	Store *tmp;
	
	for(UINT i=0;i<Width();i++)
		for(UINT j=0;j<Height();j++)
			NewImage->SetPixel(i,Height()-j-1,GetPixel(i,j));
		
		tmp=Image;
		Image=NewImage;
		delete tmp;	
		
		
		
}

void CImage::Rotate90CW()
{	
	Store *NewImage=new Store(Height(),Width(),Depth());
	Store *tmp;
	for(UINT i=0;i<Width();i++)
		for(UINT j=0;j<Height();j++)
			NewImage->SetPixel(j,Width()-i-1,GetPixel(i,j));
		tmp=Image;
		Image=NewImage;
		delete tmp;	
		
		
		
		
}


void CImage::Rotate90CCW()
{
	
	
	Store *NewImage=new Store(Height(),Width(),Depth());
	Store *tmp;
	for(UINT i=0;i<Width();i++)
		for(UINT j=0;j<Height();j++)
			NewImage->SetPixel(Height()-j-1,i,GetPixel(i,j));
		tmp=Image;
		Image=NewImage;
		delete tmp;	
		
		
		
}


void CImage::Offset(const int xOffset,const int yOffset)
{
	Store *NewImage=new Store(Width(),Height(),Depth());
	Store *tmp;
	
	for(UINT i=0;i<Width();i++)
		for(UINT j=0;j<Height();j++)
			NewImage->SetPixel((i+xOffset)%Width(),(j+yOffset)%Height(),GetPixel(i,j));
		tmp=Image;
		Image=NewImage;
		delete tmp;	
		
}



void CImage::RotateFast(double alpha)
{
	if(Image==NULL)
		return ;
	
	if(alpha==0) return ;
	if(alpha==90) {Rotate90CW(); return;}
	if(alpha==-90) {Rotate90CCW(); return;}
	Store *NewImage=new Store(Width(),Height(),Depth());
	Store *tmp;
	
	
	
	double x1,y1,xt,yt;		
	double xCenter=Width()/2.0;
	double yCenter=Height()/2.0;
	
	alpha=-alpha;
	
	
	
	for(UINT y=0;y<Height();y++)
		for(UINT x=0;x<Width();x++)			
		{ 			
			xt=(double)x-xCenter;
			yt=yCenter-(double)y;
			
			x1=xt*cos(alpha)+yt*sin(alpha);
			y1=(-1.0)*xt*sin(alpha)+yt*cos(alpha);
			
			x1+=xCenter;
			y1=yCenter-y1;
			if(x1>=0 && x1<Width() && y1>=0 && y1<Height())
			{
				NewImage->SetPixel(x,y,GetPixel((int)x1,(int)y1));
			}
		}
		
		tmp=Image;
		Image=NewImage;
		delete tmp;	
		
		return ;
		
		
}

int CImage::Rotate(double alpha)
{
	if(Image==NULL)
		return 0;
	
	if(alpha==0) return 1;
	if(alpha==90) {Rotate90CW(); return 1;}
	if(alpha==-90) {Rotate90CCW(); return 1;}
	Store *NewImage=new Store(Width(),Height(),Depth());
	Store *tmp;
	
	
	
	double x1,y1,xt,yt;		
	double xCenter=Width()/2.0;
	double yCenter=Height()/2.0;
	
	alpha=3.1415*alpha/180.0f;
	
	
	
	for(UINT y=0;y<Height();y++)
		for(UINT x=0;x<Width();x++)			
		{ 			
			xt=(double)x-xCenter;
			yt=yCenter-(double)y;
			
			x1=xt*cos(alpha)+yt*sin(alpha);
			y1=(-1.0)*xt*sin(alpha)+yt*cos(alpha);
			
			x1+=xCenter;
			y1=yCenter-y1;
			if(x1>=0 && x1<Width() && y1>=0 && y1<Height())
			{
				NewImage->SetPixel(x,y,GetPixelApproximate(x1,y1));
			}
		}
		
		tmp=Image;
		Image=NewImage;
		delete tmp;	
		
		return 1;
		
		
		
}


int CImage::Display(CDC *pDC, int xOffset, int yOffset, int width, int height)
{
	if(Image!=NULL)
		return Image->Display(pDC,xOffset,yOffset,width,height);
	else
		return -1;
	
}

rgb CImage::GetPixelSafe(UINT X, UINT Y)
{
	if(X<0)
		X=0;
	else
	{
		if(X>=Width())
			X=Width()-1;
	}
	
	if(Y<0)
		Y=0;
	else
	{
		if(Y>=Height())
			Y=Height()-1;
	}
	
	return GetPixel(X,Y);
}

BOOL CImage::SameSize(CImage &ImageToCompare)
{return (ImageToCompare.Height()==Height() &&  ImageToCompare.Width()==Width() && ImageToCompare.Depth()==Depth());}


int CImage::ChangeSize(const UINT NewWidth,const UINT NewHeight)
{
	
	if(NewWidth<1 || NewHeight<1 )
	{
		AfxMessageBox("Invalid image dimensions");
		return 0;
	}
	
	if(NewWidth==Width() && NewHeight==Height())
		return 1;
	
	
	
	
	
	if(NewWidth>Width() && NewHeight>Height())
	{
		if(NewHeight%Height()==0 && NewWidth%Width()==0)
		{
			EnlargeSizeByIntFactors(NewWidth/Width(),NewHeight/Height());
			return 1;
		}
		Store *NewImage=new Store(NewWidth,NewHeight,Depth());
		double yratio = (double)NewHeight/(double)Height(); //>1
		double xratio = (double)NewWidth/(double)Width(); // >1
		
		
		
		
		
		for(UINT i=0;i<NewWidth;i++)
			for(UINT j=0;j<NewHeight;j++)
				NewImage->SetPixel(i,j,GetPixelApproximate((double)i/xratio,(double)j/yratio));
			
			Store *tmp=Image;
			Image=NewImage;
			delete tmp;	
			
			return 1;		
	}
	
	
	
	if(NewWidth<Width() && NewHeight<Height())
	{
		if(Height()%NewHeight==0 && Width()%NewWidth==0)
		{
			ReduceSizeByIntFactors(Width()/NewWidth,Height()/NewHeight);
			return 1;
		}
		else
			ChangeSizeUsingFourier(NewWidth,NewHeight,0,1,15);
		return 1;
	}
	
	if(NewWidth<=Width() && NewHeight>=Height())
	{
		ChangeHeight(NewHeight);
		ChangeWidth(NewWidth);
		return 1;
	}
	
	if(NewWidth>=Width() && NewHeight<=Height())
	{
		ChangeWidth(NewWidth);
		ChangeHeight(NewHeight);
		return 1;
	}
	
	
	
	return 0;
	
	
}


void CImage::ChangeWidth(const UINT NewWidth)
{
	
	if(NewWidth==Width())return;
	
	
	
	
	
	if(NewWidth>Width())
	{
		Store *NewImage=new Store(NewWidth,Height(),Depth());
		Store *tmp;
		double ratio = (double)NewWidth/(double)Width();
		for(UINT i=0;i<NewWidth;i++)
			for(UINT j=0;j<Height();j++)
				NewImage->SetPixel(i,j,GetPixelApproximateByX((double)i/ratio,j));
			
			tmp=Image;
			Image=NewImage;
			delete tmp;	
			
			
			
	}
	else
	{
		ChangeWidthUsingFourier(NewWidth,0,0);
		
	}
	
	
	
}



void CImage::ChangeHeight(const UINT NewHeight)
{
	if(NewHeight==Height() || NewHeight<1)
		return;
	
	
	
	
	
	if(NewHeight>Height())
	{
		Store *NewImage=new Store(Width(),NewHeight,Depth());
		Store *tmp;
		
		double ratio = (double)NewHeight/(double)Height();
		for(UINT i=0;i<Width();i++)
			for(UINT j=0;j<NewHeight;j++)
				NewImage->SetPixel(i,j,GetPixelApproximateByY(i,(double)j/ratio));
			tmp=Image;
			Image=NewImage;
			delete tmp;	
			
	}
	else
	{
		ChangeHeightUsingFourier(NewHeight,0,0);
		
	}
	
	
	
	
}








int CImage::Allocate(UINT Width, UINT Height, UINT Depth)
{
	return Image->Allocate(Width,Height,Depth);
	
}





rgb CImage::GetPixelApproximateByX(double X, UINT Y)
{
	
	int XC=(int)(X+0.5);
	double Xo=(double)XC-0.5;
	double x=X-Xo;
	
	double c1=(1.0-x);
	double c2=x;
	
	rgb p1=GetPixelSafe(XC-1,Y);
	rgb p2=GetPixelSafe(XC,Y);
	
	
	unsigned char r=(unsigned char)(c1*(double)p1.r+(double)c2*p2.r);
	unsigned char g=(unsigned char)(c1*(double)p1.g+(double)c2*p2.g);
	unsigned char b=(unsigned char)(c1*(double)p1.b+(double)c2*p2.b);
	
	return rgb((unsigned char)r,(unsigned char)g,(unsigned char)b);
	
	
	
}

rgb CImage::GetPixelApproximateByY(UINT X, double Y)
{
	int YC=(int)(Y+0.5);
	double Yo=(double)YC-0.5;
	double y=Y-Yo;
	
	double c1=(1.0-y);
	double c2=y;
	
	rgb p1=GetPixelSafe(X,YC-1);
	rgb p2=GetPixelSafe(X,YC);
	
	
	unsigned char r=(unsigned char)(c1*(double)p1.r+(double)c2*p2.r);
	unsigned char g=(unsigned char)(c1*(double)p1.g+(double)c2*p2.g);
	unsigned char b=(unsigned char)(c1*(double)p1.b+(double)c2*p2.b);
	
	return rgb((unsigned char)r,(unsigned char)g,(unsigned char)b);
	
	
}



void CImage::Fill(rgb color)
{
	for(UINT i=0;i<Width();i++)
		for(UINT j=0;j<Height();j++)
			SetPixel(i,j,color);
		
		
}

CImage::CImage(Store *pStore)
{
	*Image=*pStore;
	
}

void CImage::AddPixel(UINT X, UINT Y, rgba color)
{
	rgb ColorInImage=GetPixel(X,Y);
	float factor=1.0-color.a/255.0;
	
	if(factor>0)
		ColorInImage.AddSmart(color*factor);
	else
		ColorInImage.SubstractSmart(color*factor);
	
    SetPixel(X,Y,ColorInImage);

}


void CImage::AddPixel(UINT X, UINT Y, rgb color,double factor)
{
	if(factor==0)
		return;
	
	rgb ColorInImage=GetPixel(X,Y);
	
	if(factor>0)
		ColorInImage.AddSmart(color*factor);
	else
		ColorInImage.SubstractSmart(color*factor);
	
    SetPixel(X,Y,ColorInImage);
	
}

double CImage::Aspect()
{
	return Width()/Height();
}

void CImage::ConvertToBW()
{
	for(UINT i=0;i<Width();i++)
		for(UINT j=0;j<Height();j++)
			SetPixel(i,j,GetPixel(i,j).GreyScale());
		
}

void CImage::ConvertToMonochrome()
{
	for(UINT i=0;i<Width();i++)
		for(UINT j=0;j<Height();j++)
			SetPixel(i,j,GetPixel(i,j).MonoChromeRand(200));
//			SetPixel(i,j,GetPixel(i,j).MonoChrome());
		
}

void CImage::EnlargeSizeByIntFactors(const UINT nx,const UINT ny)
{
	if(nx==1 && ny==1) return;
	
	
	UINT NewWidth=Width()*nx;
	UINT NewHeight=Height()*ny;
	
	if(NewHeight<1 || NewWidth<1) return;
	
	Store *NewImage=new Store(NewWidth,NewHeight,Depth());		
	
	
	for(UINT i=0;i<Width();i++)
		for(UINT j=0;j<Height();j++)
		{
			for(UINT i1=i*nx;i1<i*nx+nx;i1++)
				for(UINT j1=j*ny;j1<j*ny+ny;j1++)
					NewImage->SetPixel(i1,j1,GetPixel(i,j));
		}
		
		
		Store *tmp=Image;
		Image=NewImage;
		delete tmp;	
		
		
		
		
		return;
		
		
		
		
}

void CImage::ReduceSizeByIntFactors(const UINT nx,const UINT ny)
{
	if(nx==1 && ny==1) return;
	
	
	UINT NewWidth=Width()/nx;
	UINT NewHeight=Height()/ny;
	
	if(NewHeight<1 || NewWidth<1) return;
	
	CImage NewImage(NewWidth,NewHeight,Depth());		
	NewImage.Fill(rgb((unsigned char)0,(unsigned char)0,(unsigned char)0));	
	
	double factor=1.0/(double)(nx*ny);
	
	for(UINT i=0;i<NewWidth;i++)
		for(UINT j=0;j<NewHeight;j++)
		{
			for(UINT i1=i*nx;i1<i*nx+nx;i1++)
				for(UINT j1=j*ny;j1<j*ny+ny;j1++)
					NewImage.AddPixel(i,j,GetPixelSafe(i1,j1),factor);
		}
		//Image=NewImage.Image;
		*this=NewImage;
		return;
		
}

CImage::CImage(CImage &CI)
{
	*Image=*(CI.Image);
	
}

void CImage::FillRegion(int XL, int YL, UINT Width, UINT Height, rgb color,const float factor)
{
	color*=factor;
	
	
	
	
	for(UINT i=XL;i<XL+Width;i++)
		for(UINT j=YL;j<YL+Height;j++)
		{			
			if  (i>=0 && i<(int)CImage::Width() && j>=0 && j<(int)CImage::Height() )	
				SetPixel(i,j,color);
			//	else MessageBox("You are filling in the wrong place");
			
			//#ifdef _DEBUG 
			
			//#endif
			
		}
		
		
}






void CImage::AddRegion(const int XL,const int YL,const UINT WIDTH,const UINT HEIGHT,const rgb color,float factor)
{
	
	for(UINT i=XL;i<XL+WIDTH;i++)
		for(UINT j=YL;j<YL+HEIGHT;j++)
		{
			
			if  (i>=0 && i<(int)CImage::Width() && j>=0 && j<(int)CImage::Height() )
				
				AddPixel(i,j,color,factor);
			
		}
		
}

void CImage::AddClip(CImage& ImageClp,const int XL,const int YL,const UINT WIDTH,const UINT HEIGHT,const float factor)
{
	if (ImageClp.Width()>WIDTH || ImageClp.Height()>HEIGHT)
		return;
	
	
	int newX,newY;
	
	for(UINT i=0;i<WIDTH;i++)
		for(UINT j=0;j<HEIGHT;j++)
		{
			newX=i+XL;newY=j+YL;
			if(newX>=0 && newX<(int)Width() && newY>=0 || newY<(int)Height())
				AddPixel(newX,newY,ImageClp.GetPixel(i,j),factor);
			
		}
		return ;
		
}

void CImage::SetClip(CImage &ImageClp,const int XL,const int YL,const UINT WIDTH,const UINT HEIGHT,const float factor)
{
	if (ImageClp.Width()<WIDTH || ImageClp.Height()<HEIGHT)
		return;
	
	
	int newX,newY;
	
	for(UINT i=0;i<WIDTH;i++)
		for(UINT j=0;j<HEIGHT;j++)
		{
			newX=i+XL;newY=j+YL;
			if(newX>=0 && newX<(int)Width() && newY>=0 || newY<(int)Height())
				SetPixel(newX,newY,ImageClp.GetPixel(i,j)*factor);
			
		}
		return ;
		
}



void CImage::Invert()
{
	rgb color;
	for(UINT i=0;i<Width();i++)
		for(UINT j=0;j<Height();j++)
		{
			color=GetPixel(i,j);
			color.Invert();
			SetPixel(i,j,color);
		}
}


void CImage::ChangeSizeUsingFourier(UINT NewWidth, UINT NewHeight,UINT KernelType,float SmoothingAmount,float StepOvershoot)
{
	CTransform transform;
	transform.StatusBar = &(((CMainFrame*)AfxGetMainWnd())->m_wndStatusBar);
	int	LastPercent = 0;
	
	if(NewWidth<1 || NewHeight<1 )
	{
		AfxMessageBox("Invalid image dimensions");
		return;
	}
	
	if(NewWidth==Width() && NewHeight==Height())
		return ;


	TResample Resample;
	Resample.KernelType=(KernelType)?2:0;
	Resample.SmoothingAmount=SmoothingAmount;
	Resample.StepOvershoot=StepOvershoot;

	float	r,g,b;
	rgb	col;
	int i,j;
	const float	DitheringAmount = 1.0/RAND_MAX;
	const float	RandMax2 = RAND_MAX/2.0;

	Store *newPic=new Store(NewWidth,NewHeight,24);
	Store *tmp;
	
	transform.StartTransform();
	transform.SetText("Changing image size...");
	int	Step1Percent = 100 * (NewWidth+Width()/2.0f)*Height() / ( (NewWidth+Width()/2.0f)*Height() + NewWidth*(NewHeight+Height()/2.0f) );
	int	Step2Percent = 100 - Step1Percent;

	int MaxLen = (NewWidth>NewHeight) ? NewWidth : NewHeight;
	MaxLen = (MaxLen>Width()) ? MaxLen : Width();

	float *RData1 = new float[NewWidth*Height()];
	float *GData1 = new float[NewWidth*Height()];
	float *BData1 = new float[NewWidth*Height()];
	float *RData2 = new float[MaxLen];
	float *GData2 = new float[MaxLen];
	float *BData2 = new float[MaxLen];
	float *RData3 = new float[MaxLen];
	float *GData3 = new float[MaxLen];
	float *BData3 = new float[MaxLen];
	
	for(i=0;i<Height();i++)
	{
		for(j=0;j<Width();j++)
		{
			col = GetPixel(j,i);
			RData2[j]=(float)col.r;
			GData2[j]=(float)col.g;
			BData2[j]=(float)col.b;
		}
		Resample.Resample(RData2, Width(), RData3, NewWidth);
		Resample.Resample(GData2, Width(), GData3, NewWidth);
		Resample.Resample(BData2, Width(), BData3, NewWidth);
		for (j=0; j<NewWidth; j++) {
			RData1[j*Height()+i] = RData3[j];
			GData1[j*Height()+i] = GData3[j];
			BData1[j*Height()+i] = BData3[j];
		}
		// Update progress...
		if ((int)(Step1Percent*i/(float)Height())>LastPercent+1) {
			LastPercent = (int)(Step1Percent*i/Height());
			transform.SetProgress(LastPercent);
		}
	}

	LastPercent = 0;

	for(j=0;j<NewWidth;j++)		
	{
		Resample.Resample(RData1+Height()*j, Height(), RData3, NewHeight);
		Resample.Resample(GData1+Height()*j, Height(), GData3, NewHeight);
		Resample.Resample(BData1+Height()*j, Height(), BData3, NewHeight);

		for(i=0;i<NewHeight;i++)
		{
			r = RData3[i]+((float)rand()-RandMax2)*DitheringAmount;
			g = GData3[i]+((float)rand()-RandMax2)*DitheringAmount;
			b = BData3[i]+((float)rand()-RandMax2)*DitheringAmount;
			newPic->SetPixel(j,i,rgb(r,g,b));
		}
		// Update progress...
		if ((int)(Step2Percent*j/(float)NewWidth)>LastPercent+1) {
			LastPercent = (int)(Step2Percent*j/NewWidth);
			transform.SetProgress(Step1Percent+LastPercent);
		}
	}
		
	transform.SetProgress(100);

	delete[] RData1;
	delete[] GData1;
	delete[] BData1;
	delete[] RData2;
	delete[] GData2;
	delete[] BData2;
	delete[] RData3;
	delete[] GData3;
	delete[] BData3;

	tmp=Image;
	Image=newPic;
	delete tmp;

	transform.EndTransform();

}


void CImage::ChangeWidthUsingFourier(UINT NewWidth,UINT KernelType,float SmoothingAmount)
{
	if(NewWidth==Width())
		return;
	CSignal *InputR=new CSignal(Width());
	CSignal *InputG=new CSignal(Width());
	CSignal *InputB=new CSignal(Width());
	CSignal *OutputR,*OutputG,*OutputB;
	
	TResample Resample;
	
	if((Resample.KernelType=KernelType)==1)
		Resample.SmoothingAmount=SmoothingAmount;
	
	
	
	Store *newPic=new Store(NewWidth,Height(),24);
	Store *tmp;
	
	
	
	//Filling
	UINT i,j;
	
	float r,g,b;
	for(j=0;j<Height();j++)
	{
		for(i=0;i<Width();i++)
		{
			InputR->X[i]=(float)GetPixel(i,j).r/128.0f-1.0f;
			InputG->X[i]=(float)GetPixel(i,j).g/128.0f-1.0f;
			InputB->X[i]=(float)GetPixel(i,j).b/128.0f-1.0f;
		}
		
		OutputR=Resample.ResampleSignal(InputR,NewWidth);
		OutputG=Resample.ResampleSignal(InputG,NewWidth);
		OutputB=Resample.ResampleSignal(InputB,NewWidth);
		
		for(i=0;i<NewWidth;i++)
		{
			r=(OutputR->X[i]+1)*128;
			g=(OutputG->X[i]+1)*128;
			b=(OutputB->X[i]+1)*128;
			
			
			//validate the ranges for r,g,b		
			
			newPic->SetPixel(i,j,rgb(r,g,b));
		}
		
		
		
	}
	
	tmp=Image;
	Image=newPic;
	delete tmp;
	
	delete InputR;
	delete InputG;
	delete InputB;
	
	
}

void CImage::ChangeHeightUsingFourier(UINT NewHeight,UINT KernelType,float SmoothingAmount)
{
	if(NewHeight==Height())
		return;
	
	CSignal *InputR=new CSignal(Height());
	CSignal *InputG=new CSignal(Height());
	CSignal *InputB=new CSignal(Height());
	CSignal *OutputR,*OutputG,*OutputB;
	
	TResample Resample;
	
	Resample.KernelType=KernelType;
	Resample.SmoothingAmount=SmoothingAmount;
	
	
	
	Store *newPic=new Store(Width(),NewHeight,24);
	Store *tmp;
	
	//Filling
	UINT i,j;
	
	float r,g,b;
	for(j=0;j<Width();j++)
	{
		for(i=0;i<Height();i++)
		{
			InputR->X[i]=(float)GetPixel(j,i).r/128.0f-1.0f;
			InputG->X[i]=(float)GetPixel(j,i).g/128.0f-1.0f;
			InputB->X[i]=(float)GetPixel(j,i).b/128.0f-1.0f;
		}
		
		OutputR=Resample.ResampleSignal(InputR,NewHeight);
		OutputG=Resample.ResampleSignal(InputG,NewHeight);
		OutputB=Resample.ResampleSignal(InputB,NewHeight);
		
		for(i=0;i<NewHeight;i++)
		{
			r=(OutputR->X[i]+1)*128;
			g=(OutputG->X[i]+1)*128;
			b=(OutputB->X[i]+1)*128;
			
			
			//validate the ranges for r,g,b		
			
			newPic->SetPixel(j,i,rgb(r,g,b));
		}
	}
	
	tmp=Image;
	Image=newPic;
	delete tmp;
	
	delete InputR;
	delete InputG;
	delete InputB;
	
	
	
}

int CImage::LoadAlphaLayer(CImage &AlphaImage)
{
	if(!SameSize(AlphaImage))
		return -1;
	
	if(!HasAlpha())
		AddAlphaLayer(0);
	
	for(UINT i=0;i<Width();i++)
		for(UINT j=0;j<Height();j++)
			SetAlpha(i,j,AlphaImage.GetPixel(i,j).Grey());

	return 0;
}


rgb CImage::GetAvarageColorInRect(const int XL, const int YL, const UINT WIDTH, const UINT HEIGHT)
{
	int newX,newY;
	long r=0,g=0,b=0;
	rgb color;
	
	for(UINT i=0;i<WIDTH;i++)
		for(UINT j=0;j<HEIGHT;j++)
		{
			newX=i+XL;newY=j+YL;
			if(newX>=0 && newX<(int)Width() && newY>=0 || newY<(int)Height())
			{
				color=GetPixel(newX,newY);
				r+=color.r;
				g+=color.g;
				b+=color.b;
			}
			
			
		}
		UINT Size=WIDTH*HEIGHT;
		return rgb((unsigned char)(r/Size),(unsigned char)(g/Size),(unsigned char)(b/Size));
		
}

void CImage::SetAlphaValue(unsigned char alpha)
{
	if(!HasAlpha())
	{
		AddAlphaLayer(alpha);
	}
	else
	{
		for(UINT i=0;i<Width();i++)
			for(UINT j=0;j<Height();j++)
				SetAlpha(i,j,alpha);
	}
	
	
}



void CImage::AddAlphaLayer(unsigned char alpha)
{
	//Image->AddAlphaLayer(alpha);
	
	Store *NewImage=new Store(Width(),Height(),32);
	
	int i,j;
	for(i=0;i<Width();i++)
		for(j=0;j<Height();j++)
			NewImage->SetPixelAlpha(i,j,rgba(GetPixel(i,j),alpha));
		
		Store *tmp=Image;
		Image=NewImage;
		delete tmp;
}

void CImage::SubstractPixel(UINT X, UINT Y, rgb color, double factor)
{
	if(factor==0)
		return;
	
	rgb ColorInImage=GetPixel(X,Y);
	if(factor>0)
		ColorInImage.AddSmart(color*factor);
	else
		ColorInImage.SubstractSmart(color*factor);
	
    SetPixel(X,Y,ColorInImage);
	
}


