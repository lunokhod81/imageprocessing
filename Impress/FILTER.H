


extern "C" {
#define nsp_UsesVector
#define nsp_UsesConvolution
#include "nsp.h"
}

#ifndef _FILTER_
#define _FILTER_

class CImageFilter {
public:
	void Allocate(int NewKernelSize);
	void Normalize();
	CImageFilter();
	~CImageFilter();
	// Applies a current selected filter to array X
	// and implements boundary correction
	void	Filter1D(float *X, int Len);
	/***** These functions select the current filter *****/
	// Lowpass Gaussian filter (smoothing),
	// where WIDTH stands for a standard deviation (amount of smoothing)
	// WIDTH > 0, common settings are 0.5 < WIDTH < 10
	void	SelectGaussianFilter(float Width);
	// Highpass Gaussian filter (edge finding),
	// WIDTH > 0, common settings are 0.5 < WIDTH < 10
	void	SelectHighpassGaussianFilter(float Width);
	// You can manually select the impulse response of the filter
	// This array stores taps...
	float	*Kernel;
	// The length of the kernel
	int	KernelSize;		// MUST BE ODD !!!
	void	SelectCustomFilter(float *Data,UINT Length,BOOL Normalize);
private:
	// Remember the settings of last transform...
	int	LastKernelSize;
	int	LastArraySize;
	// ... to use the same allocated temp. storage
	//     when KernelSize and XLen are the same
	float	*Y1;
	float	*Y2;
};

#endif // _FILTER_