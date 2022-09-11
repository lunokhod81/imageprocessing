

#include "stdafx.h"
#include "filterapi.h"
#include "filter.h"
#include "filter2d.h"
#include "FloatImage.h"
//#include "image.h"
int FilterImage2d(CImage &pic,CFilter2D &filt)
{
	CFloatImage FloatImage(pic);
	FloatImage.Normalize255();
	filt.Filter2D(FloatImage.RPlane.Data,FloatImage.BPlane.Width,FloatImage.BPlane.Height);
	filt.Filter2D(FloatImage.GPlane.Data,FloatImage.GPlane.Width,FloatImage.GPlane.Height);
	filt.Filter2D(FloatImage.BPlane.Data,FloatImage.BPlane.Width,FloatImage.BPlane.Height);	

	pic.LoadFloatImage(FloatImage);



	return 0;
}


int FilterImage(CImage &pic,CImageFilter &filt)
{


	
	float **RPlane=new float*[pic.Height()];
	float **GPlane=new float*[pic.Height()];
	float **BPlane=new float*[pic.Height()];
	UINT i, j;
	for (i=0; i<pic.Height(); i++)
	{
		RPlane[i] = new float[pic.Width()];
		GPlane[i] = new float[pic.Width()];
		BPlane[i] = new float[pic.Width()];
		for (j=0; j<pic.Width(); j++)
		{
			RPlane[i][j] = pic.GetPixel(j,i).r;
			GPlane[i][j] = pic.GetPixel(j,i).g;
			BPlane[i][j] = pic.GetPixel(j,i).b;
		}
		filt.Filter1D(RPlane[i], pic.Width());
		filt.Filter1D(GPlane[i], pic.Width());
		filt.Filter1D(BPlane[i], pic.Width());
	}

	float **RVPlane=new float*[pic.Width()];
	float **GVPlane=new float*[pic.Width()];
	float **BVPlane=new float*[pic.Width()];

	for (i=0; i<pic.Width(); i++)
	{
		RVPlane[i] = new float[pic.Height()];
		GVPlane[i] = new float[pic.Height()];
		BVPlane[i] = new float[pic.Height()];
		for (j=0; j<pic.Height(); j++)
		{
			RVPlane[i][j] = RPlane[j][i];
			GVPlane[i][j] = GPlane[j][i];
			BVPlane[i][j] = BPlane[j][i];
		}
		filt.Filter1D(RVPlane[i], pic.Height());
		filt.Filter1D(GVPlane[i], pic.Height());
		filt.Filter1D(BVPlane[i], pic.Height());
	}


	for (i=0; i<pic.Width(); i++)
	{
		for (j=0; j<pic.Height(); j++)
		{
			pic.SetPixel(i,j,RGB(RVPlane[i][j], GVPlane[i][j], BVPlane[i][j]));
		}
	}


	for (i=0; i<pic.Height(); i++)
	{
		delete RPlane[i];
		delete GPlane[i];
		delete BPlane[i];
	}
	delete RPlane;
	delete GPlane;
	delete BPlane;

	for (i=0; i<pic.Width(); i++)
	{
		delete RVPlane[i];
		delete GVPlane[i];
		delete BVPlane[i];
	}
	delete RVPlane;
	delete GVPlane;
	delete BVPlane;

	return 0;
}
