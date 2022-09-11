#include "stdafx.h"
#include "DB.h"

DB::DB() 
{
	Amp2DB_Const = 20.0 / log(10);
	DB2Amp_Const = 1.0 / Amp2DB_Const;
}

double DB::Amp2DB(double amp) 
{
	if (amp<1e-30) return -600;
	return Amp2DB_Const * log(amp);
}

double DB::DB2Amp(double db)
 {
	return exp(db*DB2Amp_Const);
}

