#include "stdafx.h"
#include "rsmp.h"




TResample::TResample() {
	KernelType = 0; SmoothingAmount = 1;		// Default: Lukin filter
	StepOvershoot = 15;
	CMap = NULL;
	PMap = NULL;
	LastLen1 = LastLen2 = LastKernelType = -1;
}

TResample::~TResample() {
	delete CMap;
	delete PMap;
}

/************* MAIN RESAMPLING FUNCTION ***************/
void TResample::Resample(float *X, int Len, float *Out, int NewLen) {
	// Rebuild the kernel (if needed)...
	if ((LastKernelType!=KernelType)||(LastLen1!=Len)||(LastLen2!=NewLen)) {
		LastKernelType = KernelType;
		LastLen1 = Len;
		LastLen2 = NewLen;
		// Select new kernel...
		CKernel *KLB;
		switch (KernelType) {
			case 0 : KLB = BuildLukinKernel(); break;
			case 1 : KLB = BuildGaussKernel(); break;
			case 2 : KLB = BuildLukin2Kernel(StepOvershoot); break;
			default : KLB = BuildGaussKernel();
		}
		// Build the scaled kernel and calculate KU and KD...
		CurKernel = BuildApproximatedKernel(Len,NewLen,KLB,SmoothingAmount);
		delete KLB;
		// Do the resampling...
		ProceedResampling(X, Len, Out, NewLen);
		delete CurKernel;
	}
	else
		RepeatResampling(X, Len, Out, NewLen);
}


// Resamples the given signal to NewLen length
CSignal* TResample::ResampleSignal(CSignal *Input, int NewLen) {
	CSignal *Output = new CSignal(NewLen);
	Resample(Input->X, Input->Size, Output->X, NewLen);
	return Output;
}


/************ PRIVATE FUNCTIONS ***************/
// Builds and returns the unscaled Lukin kernel
CKernel* TResample::BuildLukinKernel() {
	int	DF = 2048;		// Downsampling factor
	int	i;
	CKernel *LK = new CKernel(4*DF+1);
	LK->DF = DF;

	fft.KernelSize = LK->Size;
	Cmplx	*FR = new Cmplx[fft.KernelSize*2];
	for (i=0; i<(fft.KernelSize-1)/DF; i++) {
		FR[i].Re = 1;
		FR[i].Im = 0;
	}
	for ( ; i<fft.KernelSize+1; i++) {
		FR[i].Re = 0;
		FR[i].Im = 0;
	}
	Cmplx *Kernel = new Cmplx[fft.KernelSize];
	fft.ConstructFIRFilter(FR, fft.KernelSize-1, StepOvershoot/*6.7*/, Kernel);
	delete[] FR;
	for (i=0; i<fft.KernelSize; i++)
		LK->X[i] = Kernel[i].Re;
	delete[] Kernel;

	LK->Normalize();
	return LK;
}

// Builds and returns the unscaled Lukin kernel with arbitrary step overshoot
CKernel* TResample::BuildLukin2Kernel(float StepOvershoot) {
	int	DF = 2048;		// Downsampling factor
	int	i;
	CKernel *LK = new CKernel(8*DF+1);
	LK->DF = DF;

	fft.KernelSize = LK->Size;
	Cmplx	*FR = new Cmplx[fft.KernelSize*2];
	for (i=0; i<(fft.KernelSize-1)/DF; i++) {
		FR[i].Re = 1;
		FR[i].Im = 0;
	}
	for ( ; i<fft.KernelSize+1; i++) {
		FR[i].Re = 0;
		FR[i].Im = 0;
	}
	Cmplx *Kernel = new Cmplx[fft.KernelSize];
	fft.ConstructFIRFilter(FR, fft.KernelSize-1, StepOvershoot, Kernel);
	delete[] FR;
	for (i=0; i<fft.KernelSize; i++)
		LK->X[i] = Kernel[i].Re;
	delete[] Kernel;

	LK->Normalize();
	return LK;
}

// Builds and returns the unscaled Gaussian kernel
CKernel* TResample::BuildGaussKernel() {
	int	DF = 2048;		// Downsampling factor
	int	i;
	CKernel *GK = new CKernel(8*DF+1);
	GK->DF = DF;

	int KerCenter = (GK->Size - 1)/2;
	for (i=0; i<GK->Size; i++)
		GK->X[i] = exp(-sqr(((float)i-KerCenter)/DF));

	GK->Normalize();
	return GK;
}

// Builds the scaled kernel from the base kernel
// Solves approximation problem for optimal KDF, KU, and KD
// Stores KU and KD coefficients
CKernel* TResample::BuildApproximatedKernel(int Len1, int Len2, CKernel *Ker, float Smoothing) {
	int	i, j;
	int	KDF;	// Kernel decimation factor
	float	fKDF;
	float	fKD;
	float	CorrectedKerDF = Ker->DF/Smoothing;
	float	LenFactor = (float)Len2/Len1;
	int	KUMax = 1 + LenFactor*CorrectedKerDF;	// Upper search limit
	float	MinDiff = 10000000;
	float	Diff;
	float	Eps1, Eps2;
	float	KFilter;
	int	BestKU;	// Best approximation
	int	BestKD;	// Best approximation
	int	BestKDF;	// Best approximation
	// Approximate KDF to meet the equation KU*KDF/KerSize = Len2/Len1
	for (KU=1; KU<KUMax; KU++) {
		fKD = (float)KU/LenFactor;
		KFilter = (KU>fKD) ? KU : fKD;		// Select the filter cutoff coefficient
		fKDF = (float)CorrectedKerDF/KFilter;
		Eps1 = fabs(fKD-Round(fKD))/fKD;
		Eps2 = fabs(fKDF-Round(fKDF))/fKDF;
		Diff = Eps1 + Eps2;
		if (Diff<MinDiff) {
			MinDiff = Diff;
			BestKD = Round(fKD);
			BestKDF = Round(fKDF);
			BestKU = KU;
		}
	}
	KDF = BestKDF;
	KU = BestKU;
	KD = BestKD;

	// Decimate the base kernel...
	int KS = 1 + 2 * (int)(Ker->Size/2/KDF);
	CKernel *Res = new CKernel(KS);
	// Find the first tap to copy...
	for (i=Ker->Size/2; i>=0; i-=KDF);
	i += KDF;
	for (j=0; j<KS; j++,i+=KDF) {
		Res->X[j] = Ker->X[i];
	}

	Res->Normalize();
	return Res;
}

#define MAP_SEPARATOR -100000

// The main resampling function
// Resamples the given signal using the current selected filter
// Does not actually perform upsampling and downsampling,
// but calculates the result signal directly from the source signal
void TResample::ProceedResampling(float *X, int Len, float *Out, int NewLen) {
	int	i;
	int	MapLen = NewLen * (CurKernel->Size / KU + 3);
	delete PMap;
	delete CMap;
	CMap = new float[MapLen];
	PMap = new int[NewLen];
	// Copy and scale the input signal
	float *Y = new float[Len];
	for (i=0; i<Len; i++)
		Y[i] = X[i] * KU;

	// Perform resampling
//	CSignal *Output = new CSignal(/*KerSize*/NewLen);
/*	for (i=0; i<KerSize; i++)
		Output->X[i] = Ker[i];
	return Output;*/

	int	PSGap = KU/2;
	float	C = (float)Len * KU / NewLen;
	int	KSGap = C/2;
	float	fCC = KSGap;
	int	ConvCenter, ConvI;
	int	Start, SPixel;
	float	Sum;
	int	CorrectBounds;
	int OutI = 0;
	int	CMapI = 0;
	int	PMapI = 0;
	// Perform the first stage: with boundary correction...
	while (fCC<Len*KU) {
		// Find starting positions for a convolution
		ConvCenter = fCC;
		Start = ConvCenter - (CurKernel->Size-1)/2;
		if (Start>=0) SPixel = (Start - PSGap + (KU-1)) / KU;
		else SPixel = (Start - PSGap) / KU;
		// Check if we need boundary correction any more...
		if (SPixel>=0) break;
		ConvI = PSGap + SPixel*KU - Start;
		PMap[PMapI++] = 0;
		Sum=0;
		if (SPixel<=0) {
			CMap[CMapI] = 0;
			for ( ; (ConvI<CurKernel->Size)&&(SPixel<=0); ConvI+=KU) {
				Sum += CurKernel->X[ConvI] * Y[0];
				CMap[CMapI] += CurKernel->X[ConvI] * KU;
				SPixel++;
			}
			CMapI++;
		}
		for ( ; (ConvI<CurKernel->Size)&&(SPixel<Len-1); ConvI+=KU) {
			Sum += CurKernel->X[ConvI] * Y[SPixel++];
			CMap[CMapI++] = CurKernel->X[ConvI] * KU;
		}
		if (SPixel>=Len-1) {
			CMap[CMapI] = 0;
			for ( ; ConvI<CurKernel->Size; ConvI+=KU) {
				Sum += CurKernel->X[ConvI] * Y[Len-1];
				CMap[CMapI] += CurKernel->X[ConvI] * KU;
			}
			CMapI++;
		}
		Out[OutI++] = Sum;
		CMap[CMapI++] = MAP_SEPARATOR;
		fCC += C;
	}
	// Perform the second stage: without boundary correction...
	while (fCC<Len*KU) {
		// Find starting positions for a convolution
		ConvCenter = fCC;
		Start = ConvCenter - (CurKernel->Size-1)/2;
		if (Start>=0) SPixel = (Start - PSGap + (KU-1)) / KU;
		else SPixel = (Start - PSGap) / KU;
		ConvI = PSGap + SPixel*KU - Start;
		// Check if we need to start boundary correction...
		if (SPixel+CurKernel->Size/KU>=Len) break;
		PMap[PMapI++] = SPixel;
		for (Sum=0; ConvI<CurKernel->Size; ConvI+=KU) {
			Sum += CurKernel->X[ConvI] * Y[SPixel++];
			CMap[CMapI++] = CurKernel->X[ConvI]*KU;
		}
		Out[OutI++] = Sum;
		CMap[CMapI++] = MAP_SEPARATOR;
		fCC += C;
	}
	// Perform the last stage: with boundary correction...
	while (fCC<Len*KU) {
		// Find starting positions for a convolution
		ConvCenter = fCC;
		Start = ConvCenter - (CurKernel->Size-1)/2;
		if (Start>=0) SPixel = (Start - PSGap + (KU-1)) / KU;
		else SPixel = (Start - PSGap) / KU;
		ConvI = PSGap + SPixel*KU - Start;
		PMap[PMapI++] = (SPixel>=0) ? SPixel : 0;
		Sum=0;
		if (SPixel<=0) {
			CMap[CMapI] = 0;
			for ( ; (ConvI<CurKernel->Size)&&(SPixel<=0); ConvI+=KU) {
				Sum += CurKernel->X[ConvI] * Y[0];
				CMap[CMapI] += CurKernel->X[ConvI] * KU;
				SPixel++;
			}
			CMapI++;
		}
		for ( ; (ConvI<CurKernel->Size)&&(SPixel<Len-1); ConvI+=KU) {
			Sum += CurKernel->X[ConvI] * Y[SPixel++];
			CMap[CMapI++] = CurKernel->X[ConvI] * KU;
		}
		if (SPixel>=Len-1) {
			CMap[CMapI] = 0;
			for ( ; ConvI<CurKernel->Size; ConvI+=KU) {
				Sum += CurKernel->X[ConvI] * Y[Len-1];
				CMap[CMapI] += CurKernel->X[ConvI] * KU;
			}
			CMapI++;
		}
		Out[OutI++] = Sum;
		CMap[CMapI++] = MAP_SEPARATOR;
		fCC += C;
	}
	delete[] Y;
}

// Repeats the last resampling over the new data
void TResample::RepeatResampling(float *X, int Len, float *Out, int NewLen) {
	// Perform resampling using PMap and CMap
	int	SPixel;
	float	Sum;
	int	CMapI = 0, PMapI = 0;
	int	OutI = 0;
	while (OutI<NewLen) {
		SPixel = PMap[PMapI++];
		Sum = 0;
		while (CMap[CMapI]!=MAP_SEPARATOR)
			Sum += CMap[CMapI++] * X[SPixel++];
		CMapI++;
		Out[OutI++] = Sum;
	}
}

