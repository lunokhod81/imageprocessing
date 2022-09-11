#ifndef _DB_
#define _DB_

#include "math.h"

class DB 
{
public:
	DB();
	double	Amp2DB(double amp);
	double	DB2Amp(double db);
private:
	double	Amp2DB_Const;
	double	DB2Amp_Const;
};

#endif

