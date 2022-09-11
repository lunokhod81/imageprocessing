
#include "stdafx.h"
#include "Signal.h"




IMPLEMENT_SERIAL(CSignal,CObject,1)

CSignal::CSignal(int Len) {
	X = new float[Len];
	Size = Len;
}

CSignal::~CSignal()
{
	delete[] X;
}


void CSignal::Resample(int NewLen,TResample *pResample)
{
	CSignal *Output=pResample->ResampleSignal(this,NewLen);
	Allocate(NewLen);
	memcpy(X, Output->X, NewLen*sizeof(float));
	delete Output;
}

void CSignal::SetValue(float value)
{
	for(int i=0;i<Size;i++)
		X[i]=value;

}

void CSignal::Allocate(int NewSize)
{
	delete [] X;
	Size=NewSize;
	X=new float[Size];
}

void CSignal::Normalize()
{
	float s = 0;
	int i;
	for (i=0; i<Size; i++)
		s += X[i];

	if(s==0)
		return;

	for (i=0; i<Size; i++)
		X[i] /= s;

}

CSignal::CSignal(CSignal &Sig)
{
	if(Size!=Sig.Size)
		Allocate(Sig.Size);

	memcpy(X,Sig.X,Size*sizeof(float));
}

CSignal& CSignal::operator =(CSignal &Sig)
{
	if(this==&Sig) return *this;

	if(Size!=Sig.Size)
		Allocate(Sig.Size);

	memcpy(X,Sig.X,Size*sizeof(float));
	return *this;
}

void CSignal::Rescale(float Factor)
{
	for(int i=0;i<Size;i++)
		X[i]*=Factor;

}

void CSignal::ResampleDefault(int NewLen)
{
	TResample Resample;
	CSignal *Output=Resample.ResampleSignal(this,NewLen);
	Allocate(NewLen);	
	memcpy(X, Output->X, NewLen*sizeof(float));
	delete Output;

}

CSignal::CSignal()
{
	X=NULL;
	Size=0;
}


void CSignal::Serialize(CArchive &ar)
{
	int i;
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		ar<<Size;
		for(i=0;i<Size;i++)
			ar<<(float)X[i];
	}
	else
	{
		// TODO: add loading code here
		ar>>Size;
		Allocate(Size);
		for(i=0;i<Size;i++)
			ar>>(float)X[i];
	}

	

}

void CSignal::ConstructFromFilter(CImageFilter &filt)
{
	if(Size!=filt.KernelSize)
		Allocate(filt.KernelSize);

	memcpy(X,filt.Kernel,filt.KernelSize*sizeof(float));

}

float CSignal::GetMaxAbs()
{
	float max=fabs(X[0]),temp;	
	for(int i=1;i<Size;i++)
	{
		temp=fabs(X[i]);
		if(max<temp)
			max=temp;			
	}
	return max;
}


CKernel::CKernel(int Size):CSignal(Size)
{
}
