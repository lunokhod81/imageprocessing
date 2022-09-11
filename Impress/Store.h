
#ifndef  _Store
#define _Store

#include "Misc.h"
#include <math.h>

#define RED rgb((unsigned char)255,(unsigned char)0,(unsigned char)0)
#define BLACK rgb((unsigned char)0,(unsigned char)0,(unsigned char)0)
#define WHITE rgb((unsigned char)255,(unsigned char)255,(unsigned char)255)
#define GREEN rgb((unsigned char)0,(unsigned char)255,(unsigned char)0)
#define BLUE rgb((unsigned char)0,(unsigned char)0,(unsigned char)255)

class rgb
{
public:
	rgb(COLORREF color);
	COLORREF GetRGB();
	static rgb Random()
	{

	rgb color;
	color.r=((float)rand()/(float)RAND_MAX)*255;
	color.g=((float)rand()/(float)RAND_MAX)*255;
	color.b=((float)rand()/(float)RAND_MAX)*255;
	return color;
	

	}
	unsigned char r,g,b;

	rgb(unsigned char R,unsigned char G,unsigned char B):r(R),g(G),b(B){}
	rgb(float R,float G,float B);
	rgb(){r=0;g=0;b=0;}

	rgb operator*(float alpha)
	{return rgb( (unsigned char)(alpha*r), (unsigned char)(alpha*g), (unsigned char)(alpha*b));}

	
	rgb operator*=(float alpha)
	{return *this*alpha;}

	BOOL operator==(rgb color){return (r==color.r)&&(g==color.g)&&(b==color.b);}
	BOOL operator>(rgb color){return (Grey()>color.Grey());}
	BOOL operator<(rgb color){return (Grey()<color.Grey());}
	/*
	rgb operator=(rgba color)
	{return rgb(color.r,color.g,color.b);}
	*/



	void AddSmart(rgb color);
	void SubstractSmart(rgb color);

	rgb operator+(rgb color)
	{
		rgb((unsigned char)(color.r+r),(unsigned char)(color.g+g),(unsigned char)(color.b+b));

	}

	rgb operator-(rgb color)
	{
		rgb((unsigned char)(color.r-r),(unsigned char)(color.g-g),(unsigned char)(color.b-b));

	}


	rgb operator+=(rgb color)
	{return *this+color;}


	
	float	Distance(rgb a) { return sqrt(sqr(a.r-r)+sqr(a.g-g)+sqr(a.b-b)); }
	float	Distance(float R, float G, float B) { return sqrt(sqr(R-r)+sqr(G-g)+sqr(B-b)); }
	static float	Distance(float R1, float G1, float B1, float R2, float G2, float B2) { return sqrt(sqr(R1-R2)+sqr(G1-G2)+sqr(B1-B2)); }
	static bool	Before(unsigned char R1, unsigned char G1, unsigned char B1, unsigned char R2, unsigned char G2, unsigned char B2) {
		if (R1>R2) return 0;
		if (R1<R2) return 1;
		if (G1>G2) return 0;
		if (G1<G2) return 1;
		if (B1>B2) return 0;
		if (B1<B2) return 1;
	}
	unsigned char Grey(){return (unsigned char)((r+g+b)/3);}
	BOOL Mono(){return Grey()>127?255:0;}
	rgb GreyScale(){ unsigned char gs=Grey();return rgb(gs,gs,gs);}
	rgb MonoChrome(){unsigned char m=Mono();return  rgb(m,m,m);}	
	rgb MonoChromeRand(float DitherAmp){float m=Grey()+((float)rand()/RAND_MAX-0.5f)*DitherAmp; m = (m>128.0)?255:0; return  rgb(m,m,m);}	
	void Invert();
};


class rgba : public rgb
{
public:
	unsigned char a;
	rgba(unsigned char R,unsigned char G,unsigned char B,unsigned char A):rgb(R,G,B),a(A){}

	rgba operator*(float alpha)
	{return rgba( (unsigned char)(alpha*r), (unsigned char)(alpha*g), (unsigned char)(alpha*b),(unsigned char)(alpha*a));}

	rgba():rgb(),a(0){}
	rgba(float R,float G,float B,float A);
	rgba(rgb color,unsigned char alpha):rgb(color),a(alpha){}


		


};










class Store
{
friend class CImage;
	
private:
	
	unsigned char *Data;
	UINT Height,Width,Depth;
	UINT Aligned32Width;
	UINT Shift;
	UINT BPP;
	BITMAPINFOHEADER ImageHeader; 

	int Allocate(UINT newWidth,UINT newHeight,UINT newDepth);
	void Free();
	void SetNewAligned32Width(UINT newWidth,UINT newDepth);
	CString FileName;

public:
	int Quantize(int nColors, unsigned char *Data, unsigned char *Palette);
	int DisplayRect(CDC *pDC,CPoint Dest,CRect RectToUpdate);
	void CompositePixel(UINT X,UINT Y,rgba color);
	rgba GetPixelAlpha(UINT X,UINT Y);
	unsigned char GetAlpha(UINT X,UINT Y);
	void SetAlpha(UINT X,UINT Y,unsigned char alpha);
	void SetPixelAlpha(UINT X,UINT Y,rgba color);
	Store(Store& S1);
	BOOL IsCorrect();
	
	void UpdateHeader();
	
	int SaveBMPFile(CString flename);
	int SaveBMPFile(CString flename, int Depth, unsigned char *Data, unsigned char *Palette);
	int ReadBMPFile(CString filename);
	Store();
	Store(UINT newWidth,UINT newHeight,UINT newDepth);
	virtual ~Store();
	Store& operator=(Store& S1);
	int Display(CDC *pDC,int xOffset,int yOffset,int width,int height);

	rgb GetPixel(UINT X,UINT Y);
	void SetPixel(UINT X,UINT Y,rgb color);
	BOOL HasAlpha(){ return Depth==32;}
};


#endif