#include "mixture_distibution.h"

#ifndef MINDOUBLE
#define MINDOUBLE 1e-15
#endif

#ifndef MAXDOUBLE
#define MAXDOUBLE 1e300
#endif

namespace distrmix
{
	double generate_value(double v1, double u1, double l1, double v2, double u2, double l2, double p)
	{
		if (v1 < -MINDOUBLE || v2 < -MINDOUBLE || p < 0 && p > 1)
		{
			return MAXDOUBLE;
		}

		double r = static_cast<double>(rand()) / RAND_MAX;

		if (r > p)
		{
			return distr::generate_value(v1, u1, l1);
		}

		else
		{
			return distr::generate_value(v2, u2, l2);
		}
	}
}