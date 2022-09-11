
#include "stdafx.h"
#include "FFT.h"

FFT::FFT() {
	AKernel = NULL;
	HKernel = NULL;
}

FFT::~FFT() {
	delete[] AKernel;
	delete[] HKernel;
}

// Perform real FFT and store amplitudes
// Input:	N real points at X->Re
// Output:	N/2+1 amps at A, X data is destroyed
void
FFT::GetSpectrum(Cmplx *X, float *A) {
	int	i, N, ND2;
	RealData	M;

	N = FFTSize;
	FFTR(X);
	M = 2.0 / N;
	ND2 = N >> 1;
	*A = X->Re / N;
	for (i=1;i<ND2;i++)
		*(A+i) = M * sqrt(sqr((X+i)->Re) + sqr((X+i)->Im));
	*(A+ND2) = (X+ND2)->Re / N;
}

// Perform real FFT and store amplitudes
// Input:	N points at X->Re, N points at X->Im
// Output:	N/2+1 amps at AR, N/2+1 amps at AI, X data is destroyed
void
FFT::GetSpectrum2(Cmplx *X, float *AR, float *AI) {
	int	i, N, ND2;
	RealData	M;

	N = FFTSize;
	FFTR2(X);
	M = 2.0 / N;
	ND2 = N >> 1;
	*AR = X->Re / N;
	*AI = (X+ND2)->Re / N;
	for (i=1;i<ND2;i++) {
		*(AR+i) = M * sqrt(sqr((X+i)->Re) + sqr((X+i)->Im));
		*(AI+i) = M * sqrt(sqr((X+i+ND2)->Re) + sqr((X+i+ND2)->Im));
	}
	*(AR+ND2) = X->Im / N;
	*(AI+ND2) = (X+ND2)->Im / N;
}


// Convert amplitudes to decibels
// Input:	X = amplitudes array
// Output:	X = decibels array
void
FFT::Amps2DBs(float *X) {
	int	i;
	for (i=0;i<=(FFTSize>>1);i++) {
		*(X+i) = db.Amp2DB(*(X+i));
	}
}


// Get the amplitude of a given frequency
double
FFT::GetFreqDB(float *X, float Freq) {
	float	FreqStep;
	long	i;
	float	ifl;
	int	x0,x1,x2,x3; // for interpolation
	double	y0,y1,y2,y3; // for interpolation

	FreqStep = SamplingRate / FFTSize;
	ifl = Freq/FreqStep;
	i = (int)ifl;
	if (i<=1) return *(X+i);
	if ((i>=(FFTSize>>1)-1)&&(i<=(FFTSize>>1))) return *(X+i);
	if (i>FFTSize/2) -1000;

	x0 = i - 1;
	x1 = x0 + 1;
	x2 = x1 + 1;
	x3 = x2 + 1;
	y0 = *(X+x0);
	y1 = *(X+x1);
	y2 = *(X+x2);
	y3 = *(X+x3);

	return y0*(ifl-x1)*(ifl-x2)*(ifl-x3)/(-6) + y1*(ifl-x0)*(ifl-x2)*(ifl-x3)/2 + y2*(ifl-x0)*(ifl-x1)*(ifl-x3)/(-2) + y3*(ifl-x0)*(ifl-x1)*(ifl-x2)/6;
}


// Complex FFT
// Input: N complex points of time domain
// Output: N complex points of frequency domain
void
FFT::FFTC(Cmplx *X) {
	int	N, M, i, j, L, LE, LE2, ip, k, s;
	Cmplx t,z;
	RealData	UR, UI, SR, SI, TR, TI;

	N = FFTSize;
	M = Round(log(N)/log(2));
	// Bit-reverse
	i = 0;
	for (s=0;s<N-1;s++) {
		if (s<i) {
			t = *(X+i); *(X+i) = *(X+s); *(X+s) = t;
		}
		k = N >> 1;
		while (i&k) k >>= 1;
		i += k;
		k <<= 1;
		while (k<N) {
			i -= k;
			k <<= 1;
		}
	}
	// First pass
	for (i=0;i<N;i+=2) {
		t = *(X+i);
		(X+i)->Re = t.Re + (X+i+1)->Re;
		(X+i)->Im = t.Im + (X+i+1)->Im;
		(X+i+1)->Re = t.Re - (X+i+1)->Re;
		(X+i+1)->Im = t.Im - (X+i+1)->Im;
	}
	// Second pass
	for (i=0;i<N;i+=4) {
		t = *(X+i);
		(X+i)->Re = t.Re + (X+i+2)->Re;
		(X+i)->Im = t.Im + (X+i+2)->Im;
		(X+i+2)->Re = t.Re - (X+i+2)->Re;
		(X+i+2)->Im = t.Im - (X+i+2)->Im;
		t = *(X+i+1);
		z = *(X+i+3);
		(X+i+1)->Re = t.Re + z.Im;
		(X+i+1)->Im = t.Im - z.Re;
		(X+i+3)->Re = t.Re - z.Im;
		(X+i+3)->Im = t.Im + z.Re;
	}
	// Last passes
	for (L=3;L<=M;L++) {
		LE = 1 << L;
		LE2 = LE >> 1;
		UR = 1; UI = 0;
		SR = cos(M_PI/LE2);
		SI =	-sin(M_PI/LE2);
		for (j=0;j<LE2;j++) {
			for (i=j;i<N;i+=LE) {
				ip = i + LE2;
				TR = (X+ip)->Re*UR - (X+ip)->Im*UI;
				TI = (X+ip)->Re*UI + (X+ip)->Im*UR;
				(X+ip)->Re = (X+i)->Re - TR;
				(X+ip)->Im = (X+i)->Im - TI;
				(X+i)->Re = (X+i)->Re + TR;
				(X+i)->Im = (X+i)->Im + TI;
			}
			TR = UR;
			UR = TR*SR - UI*SI;
			UI = TR*SI + UI*SR;
		}
	}
}

// Real FFT
// Input: N real points at Re, anything at Im
// Output: N/2+1 real freqs, N/2+1 imaginary freqs
void
FFT::FFTR(Cmplx *X) {
	int	N, ND2, ND4;
	int	i, im, ip2, ipm, ip;
	RealData	UR, UI, SR, SI, TR, TI;

	// Separate even and odd points
	N = FFTSize;
	ND2 = N>>1;
	ND4 = ND2>>1;
	for (i=0;i<ND2;i++) {
		(X+i)->Re = (X+(i<<1))->Re;
		(X+i)->Im = (X+(i<<1)+1)->Re;
	}
	// Calculate N/2 point FFT
	FFTSize = ND2;
	FFTC(X);
	FFTSize = N;
	// Even/odd frequency domain decomposition
	for (i=1;i<ND4;i++) {
		im = ND2 - i;
		ip2 = i + ND2;
		ipm = im + ND2;
		(X+ipm)->Re = (X+ip2)->Re = ((X+i)->Im + (X+im)->Im)*0.5;
		(X+ip2)->Im = ((X+i)->Re - (X+im)->Re)*(-0.5);
		(X+ipm)->Im =  - (X+ip2)->Im;
		(X+im)->Re = (X+i)->Re = ((X+i)->Re + (X+im)->Re)*0.5;
		(X+i)->Im = ((X+i)->Im - (X+im)->Im)*0.5;
		(X+im)->Im = - (X+i)->Im;
	}
	(X+N*3/4)->Re = (X+ND4)->Im;
	(X+ND2)->Re = X->Im;
	(X+ND2+ND4)->Im = (X+ND2)->Im = (X+ND4)->Im = X->Im = 0;
	// Complete the last FFT stage
	// First step: calculate X[0] and X[N/2]
	TR = (X+ND2)->Re;
	TI = (X+ND2)->Im;
	(X+ND2)->Re = X->Re - TR;
	(X+ND2)->Im = X->Im - TI;
	X->Re = X->Re + TR;
	X->Im = X->Im + TI;
	// Other steps
	UR = SR = cos(M_PI/ND2);
	UI = SI = -sin(M_PI/ND2);
	ip = ND2+1;
	for (i=1;i<ND2;i++,ip++) {
/*		TR = (X+ip)->Re*UR - (X+ip)->Im*UI;
		TI = (X+ip)->Re*UI + (X+ip)->Im*UR;
		(X+ip)->Re = (X+i)->Re - TR;
		(X+ip)->Im = (X+i)->Im - TI;
		(X+i)->Re = (X+i)->Re + TR;
		(X+i)->Im = (X+i)->Im + TI;*/
		(X+i)->Re = (X+i)->Re + (X+ip)->Re*UR - (X+ip)->Im*UI;
		(X+i)->Im = (X+i)->Im + (X+ip)->Re*UI + (X+ip)->Im*UR;
		TR = UR;
		UR = TR*SR - UI*SI;
		UI = TR*SI + UI*SR;
	}
}


// Double (stereo) real FFT
// Input: N left points at Re, N right points at Im
// Output: N/2 left complex freqs, N/2 right complex freqs (X[0]->Im = max. cosine freq)
void
FFT::FFTR2(Cmplx *X) {
	int	i, im, N, ND2;
	Cmplx	A, B;
	RealData	t;

	N = FFTSize;
	ND2 = N>>1;
	// Calculate N point FFT
	FFTC(X);
	// Even/odd frequency domain decomposition
	for (i=1;i<ND2;i++) {
		im = N - i;
		A = *(X+i);
		B = *(X+im);
		(X+i)->Re  = (A.Re + B.Re) * 0.5;
		(X+i)->Im = (A.Im - B.Im) * 0.5;
		(X+im)->Re  = (A.Im + B.Im) * 0.5;
		(X+im)->Im  = (A.Re - B.Re) * (-0.5);
	}
	// Place DC 2 to X2[0]->Re and max cosine freq 1 to X2[0]->Im
	t = X->Im; X->Im = (X+ND2)->Re; (X+ND2)->Re = t;
}



// Inverse complex FFT
// Input: N complex points of frequency domain
// Output: N complex points of time domain
void
FFT::IFFTC(Cmplx *X) {
	int	i;
	RealData	DivFFTSize = 1.0 / FFTSize;

	// Change the sign of ImX
	for (i=0;i<FFTSize;i++) (X+i)->Im = -((X+i)->Im);
	// Calculate N point complex FFT
	FFTC(X);
	// Adjust the result data
	for (i=0;i<FFTSize;i++) {
		(X+i)->Re *= DivFFTSize;
		(X+i)->Im = -((X+i)->Im) * DivFFTSize;
	}
}

// Inverse real FFT
// Input: N/2+1 complex points of frequency domain at X[0]...X[FFTSize/2]
// Output: X->Re contains N real points of time domain
/******************************** INCOMPLETE **********************/
void
FFT::IFFTR(Cmplx *X) {
	int	i;
	RealData	DivFFTSize = 1.0 / FFTSize;

	// Adjust the input data
	for (i=FFTSize/2+1;i<FFTSize;i++) {
		(X+i)->Re = (X+FFTSize-i)->Re;
		(X+i)->Im = -((X+FFTSize-i)->Im);
	}
	for (i=0;i<FFTSize;i++) (X+i)->Re += (X+i)->Im;
	// Calculate N point real FFT
	FFTR(X);
	// Adjust the result data
	for (i=FFTSize/2+1;i<FFTSize;i++) {
		(X+i)->Re = (X+FFTSize-i)->Re;
		(X+i)->Im = -((X+FFTSize-i)->Im);
	}
	for (i=0;i<FFTSize;i++) (X+i)->Re = ((X+i)->Re + (X+i)->Im) * DivFFTSize;
}


void
FFT::ApplyWindow(Cmplx *X, int Type) {
	int	i, N;
	RealData	h, x;

	N = FFTSize;
	for (i=0;i<N/2;i++) {
		x = i;
		switch (Type) {
			case WINDOW_RECTANGLE	: h = 1; break;
			case WINDOW_HAMMING	: h = 0.42 - 0.5*cos(2*M_PI*x/N) + 0.08*cos(4*M_PI*x/N); break;
			case WINDOW_BLACKMAN	: h = 0.54 - 0.46*cos(2*M_PI*x/N); break;
			case WINDOW_TRIANGLE	: h = 2*x/N; break;
			case WINDOW_HANNING	: h = 0.5 - 0.5*cos(2*M_PI*x/N); break;
		}
		(X+i)->Re *= h;
		(X+i)->Im *= h;
		(X+N-i-1)->Re *= h;
		(X+N-i-1)->Im *= h;
	}
}

// Calculate Bessel function
long double
FFT::I0(long double X) {
	long double	Y, T, E, DE, SDE;
	int	i;

	Y = X/2;
	T = 0.0000000001;
	E = DE = 1;
	for (i=1;i<50;i++) {
		DE *= Y / i;
		SDE = DE * DE;
		E += SDE;
		if (E*T-SDE>0) break;
	}
	return E;
}

// Applies Kaiser window to the real part of X
// Len must be odd!!!
void
FFT::ApplyKaiserWindow(Cmplx *X, int Len, long double b) {
	int	i, k;
	long double	iI0b = 1.0 / I0(b);
	long double	h;

	k = -(Len>>1);
	for (i=0;i<(Len>>1);i++,k++) {
		h = I0(b*sqrt(1-sqr(2.0*k/(Len-1)))) * iI0b;
		(X+i)->Re *= h;
		(X+Len-1-i)->Re *= h;
	}
}


void
FFT::ApplyKaiserWindow(Cmplx *X, long double b) {
	int	i, k;
	long double	iI0b = 1.0 / I0(b);
	long double	h;
	int	Len = FFTSize-1;
	double	Sum = 0;

	k = -(Len>>1);
	for (i=0;i<(Len>>1);i++,k++) {
		h = I0(b*sqrt(1-sqr(2.0*k/(Len-1)))) * iI0b;
		Sum += h;
		(X+i)->Re *= h;
		(X+Len-1-i)->Re *= h;
	}
	Sum /= (Len>>1);
	Sum = 1/Sum;
	for (i=0;i<Len;i++) (X+i)->Re *= Sum;
	(X+Len)->Re = 0;
}


void
FFT::ApplyWindowEx(Cmplx *X, RealData K, RealData f) {
	int	i, N;
	RealData	h, x;

	N = FFTSize;
	for (i=0;i<N/2-1;i++) {
		x = i;
		h = K * sin(2*M_PI*f*(x-N/2))/(x-N/2) * (0.42 - 0.5*cos(2*M_PI*x/N) + 0.08*cos(4*M_PI*x/N));
		(X+i)->Re *= h;
		(X+i)->Im *= h;
		(X+N-i-1)->Re *= h;
		(X+N-i-1)->Im *= h;
	}
}


// Applies a window to a filter's kernel
/*void
FFT::ApplyKernelWindow(Cmplx *X, int Type) {
	int	i, N;
	RealData	h, x;

	N = FFTSize;
	for (i=0;i<N/2;i++) {
		x = i;
		switch (Type) {
			case WINDOW_RECTANGLE	: h = 1; break;
			case WINDOW_HAMMING	: h = 0.42 - 0.5*cos(2*M_PI*x/N) + 0.08*cos(4*M_PI*x/N); break;
			case WINDOW_BLACKMAN	: h = 0.54 - 0.46*cos(2*M_PI*x/N); break;
			case WINDOW_TRIANGLE	: h = 2*x/N; break;
			case WINDOW_HANNING	: h = 0.5 - 0.5*cos(2*M_PI*x/N); break;
		}
		(X+i)->Re *= h;
		(X+i)->Im *= h;
		(X+N-i-1)->Re *= h;
		(X+N-i-1)->Im *= h;
	}
} */

/***************** FILTERS, CONVOLUTIONS ******************/

// Returns amplitude (dB) of A-weighting curve for a given frequency
float
FFT::ACurve(float F) {
	float	AFreq[] = {-2,   -1,   0,  20,  30,  50,  90, 200, 400,  850, 2000, 2500, 7000, 20000, 200000, 201000, 202000};
	float	AAmp[]  = {-80, -80, -80, -50, -40, -30, -20, -10, -4.5,   0,  2.3,  2.5,    0,    -9,    -80,    -80,    -80};
	int	i;
	float	x0,x1,x2,x3; // for interpolation
	float	y0,y1,y2,y3; // for interpolation

	for (i=0; AFreq[i]<=F; i++);
	i--;
	x0 = AFreq[i-1];
	x1 = AFreq[i];
	x2 = AFreq[i+1];
	x3 = AFreq[i+2];
	y0 = AAmp[i-1];
	y1 = AAmp[i];
	y2 = AAmp[i+1];
	y3 = AAmp[i+2];

	return y0*(F-x1)*(F-x2)*(F-x3)/((x0-x1)*(x0-x2)*(x0-x3))
	+ y1*(F-x0)*(F-x2)*(F-x3)/((x1-x0)*(x1-x2)*(x1-x3))
	+ y2*(F-x0)*(F-x1)*(F-x3)/((x2-x0)*(x2-x1)*(x2-x3))
	+ y3*(F-x0)*(F-x1)*(F-x2)/((x3-x0)*(x3-x1)*(x3-x2));
}


// Returns amplitude (dB) of Hearing curve for a given frequency
float
FFT::HearingCurve(float F) {
	float	AFreq[] = {-2,   -1,   0,  20,  30,  50,  90, 200, 400,  850, 1500, 2500, 7000, 15000, 19000, 20000, 20500, 21400, 21700, 21800, 21950, 22050, 200000, 201000, 202000};
	float	AAmp[]  = {20,   20,  20,  20,  20,  18,  15,  10,   5,    0,  -10,  -12,   -5,    17,    24,    25,    25,    23,    15,    10,     5,     0,      0,      0,      0};
	int	i;
	float	x0,x1,x2,x3; // for interpolation
	float	y0,y1,y2,y3; // for interpolation

	for (i=0; AFreq[i]<=F; i++);
	i--;
	x0 = AFreq[i-1];
	x1 = AFreq[i];
	x2 = AFreq[i+1];
	x3 = AFreq[i+2];
	y0 = AAmp[i-1];
	y1 = AAmp[i];
	y2 = AAmp[i+1];
	y3 = AAmp[i+2];

	return y0*(F-x1)*(F-x2)*(F-x3)/((x0-x1)*(x0-x2)*(x0-x3))
	+ y1*(F-x0)*(F-x2)*(F-x3)/((x1-x0)*(x1-x2)*(x1-x3))
	+ y2*(F-x0)*(F-x1)*(F-x3)/((x2-x0)*(x2-x1)*(x2-x3))
	+ y3*(F-x0)*(F-x1)*(F-x2)/((x3-x0)*(x3-x1)*(x3-x2));
}


void
FFT::GenerateACurve(Cmplx *X, int aFFTSize) {
	int	i;
	float	f, fStep;

	fStep = SamplingRate / aFFTSize;
	for (i=0; i<=(aFFTSize>>1); i++) {
		f = fStep * i;
		(X+i)->Re = db.DB2Amp(ACurve(f));
		(X+i)->Im = 0;
	}
}

void
FFT::GenerateHearingCurve(Cmplx *X, int aFFTSize) {
	int	i;
	float	f, fStep;

	fStep = SamplingRate / aFFTSize;
	for (i=0; i<=(aFFTSize>>1); i++) {
		f = fStep * i;
		(X+i)->Re = db.DB2Amp(HearingCurve(f));
		(X+i)->Im = 0;
	}
}


// Calculate windowed frequency response of the FIR filter
// Input: X contains a complex frequency response (size of array must be Len*2) (for linear phase use only real part),
//        Len+1 is a length of frequency response, must be a power of 2
//        KernelSize is a desired kernel length, must be 2*k+1
//        B is a constant for Kaiser window
//        Y contains (KernelSize) complex points: a storage place for generated complex frequency response
// Output: Y = KLen/2+1 complex points of generated kernel at time domain
void
FFT::ConstructFIRFilter(Cmplx *X, int Len, float B, Cmplx *Y) {
	int	i, j;
	int	DefFFTSize = FFTSize;

	FFTSize = Len<<1;
	// Calculate the kernel of the filter
	IFFTR(X);
	// Shift it and truncate
	for (i=(Len<<1)-((KernelSize+1)>>1)+1,j=0; i<(Len<<1); i++,j++)
		(Y+j)->Re = (X+i)->Re;
	for (i=0; i<((KernelSize+1)>>1); i++,j++)
		(Y+j)->Re = (X+i)->Re;
	// Apply the desired window
	ApplyKaiserWindow(Y, KernelSize, B);
//	(Y+KernelSize)->Re = 0;		// ???????????????????????

	FFTSize = DefFFTSize;
}


// Converts zero-padded kernel into frequency domain for further FFT-convolution
// Input:	K contains kernel
// Output:	FR contains (DesiredFFTSize/2+1) points of desired frequency response
void
FFT::PrepareKernelFR(Cmplx *K, Cmplx *FR, int DesiredFFTSize) {
	int DefFFTSize = FFTSize;
	int	i;
	// Copying and zero-padding kernel
	for (i=0;i<KernelSize;i++) *(FR+i) = *(K+i);
	for (i=KernelSize;i<DesiredFFTSize;i++) (FR+i)->Re = (FR+i)->Im = 0;
	// Converting kernel into frequency domain
	FFTSize = DesiredFFTSize;
	FFTR(FR);
	FFTSize = DefFFTSize;
}

// Single step convolution via FFT
// Input:	(Len) complex points of data X in time domain (Len = any integer, but Len<=FRSize-KernelSize+1),
//          FR contains frequency response of sufficient size (FFTSize/2+1)
// Output:	Y contains N complex points in time domain (N = 2**k+KernelSize)
void
FFT::ConvRSingle(Cmplx *X, int Len, Cmplx *FR, int FRSize, Cmplx *Y) {
	int	DefFFTSize = FFTSize;
	int	FFTSize2 = FRSize>>1;
	int	i;
	RealData	OldRe;

	// Copying and zero-padding data
	for (i=0;i<Len;i++) *(Y+i) = *(X+i);
	for (i=Len;i<FRSize;i++) (Y+i)->Re = (Y+i)->Im = 0;
	// Converting data into frequency domain
	FFTSize = FRSize;
	FFTR(Y);
	// Multiplying frequencies
	for (i=0;i<=FFTSize2;i++) {
		OldRe = (Y+i)->Re;
		(Y+i)->Re = OldRe * (FR+i)->Re - (Y+i)->Im * (FR+i)->Im;
		(Y+i)->Im = OldRe * (FR+i)->Im + (Y+i)->Im * (FR+i)->Re;
	}
	// Converting data back into time domain
	IFFTR(Y);
	FFTSize = DefFFTSize;
}


// Multy step convolution via FFT
// Input:	(Len) complex points of data in time domain at X,
//          K contains (KernelSize) complex points of kernel
// Output:	Y->Re contains ((FFTSize/2)*(N+1/2)) complex points in time domain
void
FFT::ConvRMulty(Cmplx *X, int Len, Cmplx *K, Cmplx *Y, Cmplx *KFR, Cmplx *Temp) {
	int	i, Step, Ofs;
	int	CFFTSize, DataBlockSize;
	int	ResultLen = Len + KernelSize - 1;

	CFFTSize = (KernelSize<<1) - 2;
	DataBlockSize = CFFTSize - KernelSize + 1;
	PrepareKernelFR(K, KFR, CFFTSize);
	// Reset the result array with zeroes
	for (i=0;i<ResultLen;i++) (Y+i)->Re = 0;
	// Calculate overlap&add convolutions
	for (Step=0,Ofs=0; Ofs+DataBlockSize<=Len; Step++,Ofs+=DataBlockSize) {
		ConvRSingle(X+Ofs, DataBlockSize, KFR, CFFTSize, Temp);
		for (i=0;i<CFFTSize;i++) (Y+Ofs+i)->Re += (Temp+i)->Re;
	}
	// Calculate the last convolution (incomplete size)
	ConvRSingle(X+Ofs, Len-Ofs, KFR, CFFTSize, Temp);
	for (i=0;i<ResultLen-Ofs;i++) (Y+Ofs+i)->Re += (Temp+i)->Re;
}


// Input: X contains (Len) real time-domain samples
// Output: Y contains output real time-domain samples
void
FFT::AWeightingFilter(Cmplx *X, int Len, Cmplx *Y) {
	// If kernel was not generated yet - generate it
	if (!AKernel) {
		Cmplx	*A_FR = new Cmplx[8192];
		GenerateACurve(A_FR, 8192);
		KernelSize = 4097;
		AKernel = new Cmplx[KernelSize];
		ConstructFIRFilter(A_FR, KernelSize-1, 4, AKernel);
		delete[] A_FR;
	}
	// Perform OLA convolution
	KernelSize = 4097;
	Cmplx	*T1 = new Cmplx[8192];
	Cmplx	*T2 = new Cmplx[8192];
	ConvRMulty(X, Len, AKernel, Y, T1, T2);
	delete[] T1;
	delete[] T2;

}


// Input: X contains (Len) real time-domain samples
// Output: Y contains output real time-domain samples
void
FFT::HearingWeightingFilter(Cmplx *X, int Len, Cmplx *Y) {
	// If kernel was not generated yet - generate it
	if (!HKernel) {
		Cmplx	*A_FR = new Cmplx[8192];
		GenerateHearingCurve(A_FR, 8192);
		KernelSize = 4097;
		HKernel = new Cmplx[KernelSize];
		ConstructFIRFilter(A_FR, KernelSize-1, 4, HKernel);
		delete[] A_FR;
	}
	// Perform OLA convolution
	KernelSize = 4097;
	Cmplx	*T1 = new Cmplx[8192];
	Cmplx	*T2 = new Cmplx[8192];
	ConvRMulty(X, Len, HKernel, Y, T1, T2);
	delete[] T1;
	delete[] T2;

}









