
#include "FFT.h"


class CSignal;
class CKernel;

#ifndef _RESAMPLING_
#define _RESAMPLING_
#include "Signal.h"



/******* CLASS FOR STORING A BASE (NON-SCALED) KERNEL ************/






/************ CLASS FOR RESAMPLING A 1D SIGNAL *********/
class TResample {
public:
	TResample();
	~TResample();
	// Main resampling function
	CSignal* ResampleSignal(CSignal *Input, int NewLen);
	void	Resample(float *X, int Len, float *Out, int NewLen);
	int	KernelType;
	// 0 = Lukin filter (default)
	// 1 = Gaussian filter
	// 2 = Lukin filter with variable step overshoot
	float	SmoothingAmount;
	// Smoothing amount for filter kernels.
	// Appropriate values lie between 0.7 and 5 (2 is default) for Gaussian filter
	// and between 0.92 and 2 (1 is default) for Lukin filter
	float	StepOvershoot;
	// Step response overshoot parameter for Lukin2 kernel.
	// Appropriate values lie between 5 and 20
private:
	// Builds the unscaled Gaussian kernel
	CKernel	*BuildGaussKernel();
	// Builds the unscaled Lukin kernel
	CKernel	*BuildLukinKernel();
	// Builds the Lukin kernel with arbitrary step overshoot
	CKernel	*BuildLukin2Kernel(float StepOvershoot);
	// Builds the scaled kernel from the base kernel
	CKernel	*BuildApproximatedKernel(int Len1, int Len2, CKernel *Ker, float Smoothing=1);
	int	KU, KD;		// Upsampling and downsampling coefficients
	CKernel	*CurKernel;		// Current selected kernel
	// Map of resampling coefficients
	float	*CMap;
	// Map of pixels indexes and separators
	int	*PMap;
	// Does the resampling
	void	ProceedResampling(float *X, int Len, float *Out, int NewLen);
	void	RepeatResampling(float *X, int Len, float *Out, int NewLen);
	// DSP routines...
	FFT	fft;
	// Last used settings...
	int	LastLen1, LastLen2, LastKernelType;
};



#endif

