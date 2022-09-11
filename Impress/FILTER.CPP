

#include "stdafx.h"
#include "misc.h"
#include "filter.h"
#include "math.h"


CImageFilter::CImageFilter() {
	Kernel = NULL;
	LastKernelSize = 0;
	LastArraySize = 0;
	Y1 = NULL; Y2 = NULL;
}

CImageFilter::~CImageFilter() {
	if (Kernel) nspFree(Kernel);
	if (Y1) {
		nspFree(Y2);
		nspFree(Y1);
	}
}


// Filters the input 1D-array with the current selected Kernel
// In-place operation
// Boundary correction is implemented
void CImageFilter::Filter1D(float *X, int Len) {
	int	BorderWidth = (KernelSize-1)/2;
	// Check if we can use old temp. storage
	if ((KernelSize!=LastKernelSize)||(Len!=LastArraySize)) {
		// Allocate new temp. storage
		if(Y2) nspFree(Y2);
		if(Y1) nspFree(Y1);
		Y1 = nspsMalloc(Len+BorderWidth*2);
		Y2 = nspsMalloc(Len+BorderWidth*2+KernelSize-1);
		LastArraySize = Len;
		LastKernelSize = KernelSize;
	}
	// Copy the source array into Y1 and extend its boundaries
	nspsbSet(X[0], Y1, BorderWidth);
	nspsbCopy(X, Y1+BorderWidth, Len);
	nspsbSet(X[Len-1], Y1+Len+BorderWidth, BorderWidth);
	// Perform the convolution
	nspsConv(Y1, Len+BorderWidth*2, Kernel, KernelSize, Y2);
	// Copy the result array Y2 into X
	nspsbCopy(Y2+BorderWidth*2, X, Len);
}

// Selects Gaussian filter kernel with the desired smoothing amount (Width)
// 0 < Width < 1000 
void CImageFilter::SelectGaussianFilter(float Width) {
	int	i;
	if (Kernel) nspFree(Kernel);
	KernelSize = Width*5;
	// KernelSize must be odd
	KernelSize |= 1;
	if (KernelSize<3) KernelSize = 3;
	Kernel = nspsMalloc(KernelSize);
	int KerCenter = (KernelSize-1)/2;
	for (i=0; i<KernelSize; i++)
		Kernel[i] = exp(-sqr((float)(i-KerCenter))/sqr(Width));
	// Normalise the amplitude of the kernel
	float s = 0;
	for (i=0; i<KernelSize; i++) s += Kernel[i];
	for (i=0; i<KernelSize; i++) Kernel[i] /= s;

}

// Selects high-pass Gaussian filter kernel with the desired smoothing amount (Width)
// 0 < Width < 1000
void CImageFilter::SelectHighpassGaussianFilter(float Width) {
	int	i;
	SelectGaussianFilter(Width);
	// Inverse taps
	for (i=0; i<KernelSize; i++)
		Kernel[i] = -Kernel[i];
	// Add 1.0 to the central tap
	Kernel[KernelSize/2] += 1;
}



void CImageFilter::SelectCustomFilter(float *Data,UINT Length,BOOL Normalize=TRUE)
{
	UINT i;
	if (Kernel) nspFree(Kernel);
	KernelSize = Length;  // MUST BE ODD
	Kernel = nspsMalloc(KernelSize);
	// Fill the kernel here...
	for (i=0; i<KernelSize; i++)
		Kernel[i] = Data[i];
	

	// Normalise the amplitude of the kernel
	if(Normalize)	
		CImageFilter::Normalize();
}

void CImageFilter::Normalize()
{
	float s = 0;
	for (int i=0; i<KernelSize; i++) s += Kernel[i];

	if(s==0)
		return;

	for (i=0; i<KernelSize; i++) Kernel[i] /= s;

}

void CImageFilter::Allocate(int NewKernelSize)
{
	if (Kernel) nspFree(Kernel);
	KernelSize = NewKernelSize;  // MUST BE ODD
	Kernel = nspsMalloc(KernelSize);
}
