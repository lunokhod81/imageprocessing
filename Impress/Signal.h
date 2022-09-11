//class CSignal;
class TResample;



#ifndef _CSignal_
#define  _CSignal_



#include "Rsmp.h"
#include "Filter.h"



class CSignal:public CObject
{
public:
	float GetMaxAbs();
	void ConstructFromFilter(CImageFilter &filt);
	virtual void Serialize(CArchive& ar);
	DECLARE_SERIAL( CSignal)
    
	CSignal();
	void ResampleDefault(int NewLen);
	void Rescale(float Factor);
	CSignal(CSignal &Sig);
	void Normalize();
	void Allocate(int NewSize);
	void SetValue(float value);
	CSignal(int Len);
	~CSignal();
	void Resample(int NewLen,TResample *pResample);
	CSignal &operator=(CSignal &Sig);
	float *X;  //Main data
	int	Size;
};


class CKernel : public CSignal
{
public:
	CKernel(int Size);
	float	DF;	// Downsampling factor for this kernel
	
};



#endif
