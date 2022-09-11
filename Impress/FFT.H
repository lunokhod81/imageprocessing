//fft,h

#ifndef _FFT_
#define _FFT_


#include "misc.h"
#include "DB.h"
/*

  include "DB.h"
Speed for 65536 points (float):

Real FFT (FFTR)			80 ms
Cmplx FFT (FFTC)			161 ms
Stereo real FFT (FFTR2)	166 ms


Spectral noise (FFT size = 65536):

float        -100 dB
double       -270 dB
long double  -330 dB


Waveform noise after FFTR - IFFTR (FFT size = 65536):

float        -60 dB
double       -230 dB
long double  -290 dB

*/

#define WINDOW_RECTANGLE	0
#define WINDOW_HAMMING	1
#define WINDOW_BLACKMAN	2
#define WINDOW_BARTLETT	3
#define WINDOW_TRIANGLE	3
#define WINDOW_HANNING	4
#define M_PI 3.14159265358979


typedef float	RealData;

typedef struct C {
	RealData	Re;
	RealData	Im;
} Cmplx;

class FFT {
public:
	FFT();
	~FFT();

	/***************** DISCRETE FOURIER TRANSFORMS *****************/

	// Spectral analysys
	void	GetSpectrum	(Cmplx *X, float *A);		// Perform real FFT and store amplitudes
	void	GetSpectrum2	(Cmplx *X, float *AR, float *AI);		// Perform stereo real FFT and store amplitudes to AR and AI
	void	Amps2DBs	(float *X);		// Convert amplitudes to decibels
	double	GetFreqDB	(float *X, float Freq);	// Get the amplitude (dB) of a given frequency

	// FFT functions
	void	FFTC	(Cmplx *X);		// Complex FFT
	void	FFTR	(Cmplx *X);		// Real FFT
	void	FFTR2	(Cmplx *X);		// Double (stereo) real FFT

	// Inverse FFT functions
	void	IFFTC	(Cmplx *X);		// Inverse complex FFT
	void	IFFTR	(Cmplx *X);		// Inverse real FFT

	void	ApplyWindow	(Cmplx *X, int Type);
	void	ApplyWindowEx	(Cmplx *X, RealData K, RealData f);
	void	ApplyKaiserWindow(Cmplx *X, int Len, long double b);		// Filters version
	void	ApplyKaiserWindow(Cmplx *X, long double b);		// Common real version

	/***************** FILTERS, CONVOLUTIONS *****************/

	void	GenerateACurve(Cmplx *X, int FFTSize);
	void	GenerateHearingCurve(Cmplx *X, int FFTSize);
	// Constructs FIR filter with the desired frequency response
	void	ConstructFIRFilter(Cmplx *X, int Len, float B, Cmplx *Y);
	// Convolution via FFT
	void	PrepareKernelFR(Cmplx *K, Cmplx *FR, int DesiredFFTSize);
	void	ConvRSingle(Cmplx *X, int Len, Cmplx *FR, int FRSize, Cmplx *Y);		// Single step convolution
	void	ConvRMulty(Cmplx *X, int Len, Cmplx *K, Cmplx *Y, Cmplx *KFR, Cmplx *Temp);		// Convolution of the long signal (step by step)
	void	AWeightingFilter(Cmplx *X, int Len, Cmplx *Y);		// Applies A-weighting filter
	void	HearingWeightingFilter(Cmplx *X, int Len, Cmplx *Y);		// Applies A-weighting filter

	int	FFTSize;
	float	SamplingRate;
	int	KernelSize;		// Size of kernel - 1
private:
	long double	I0(long double X);
	float	ACurve(float Freq);
	float	HearingCurve(float Freq);
	Cmplx	*AKernel;
	Cmplx	*HKernel;
	DB	db;
};

#endif