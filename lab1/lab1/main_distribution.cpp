#include "main_distribution.h"

#ifndef MINDOUBLE
#define MINDOUBLE 1e-15
#endif

#ifndef PI
#define PI 3.14159265359
#endif

namespace distr
{
	double generate_value(double v, double u, double l)
	{
		if (v < -MINDOUBLE)
		{
			return INFINITY;
		}

		double r1 = static_cast<double>(rand()) / RAND_MAX;
		double r2 = static_cast<double>(rand()) / RAND_MAX;

		return u + l * sqrt(1 - pow(r1, 1 / (v + 0.5))) * cos(2 * PI * r2);
	}

	double get_density(double x, double v, double u, double l)
	{
		if (v < -MINDOUBLE)
		{
			return INFINITY;
		}

		double result = pow((1 - pow((x - u) / l, 2)) / 4, v) / (2 * beta(v + 1, v + 1) * l);
		result = result > 0 ? result : 0;

		return result;
	}

	double get_expected_value(double v, double u, double l)
	{
		if (v < -MINDOUBLE)
		{
			return INFINITY;
		}

		return u;
	}

	double get_dispersion(double v, double u, double l)
	{
		if (v < -MINDOUBLE)
		{
			return INFINITY;
		}

		return pow(l, 2) / (2 * v + 3);
	}

	double get_skewness(double v, double u, double l)
	{
		if (v < -MINDOUBLE)
		{
			return INFINITY;
		}

		return 0;
	}

	double get_kurtosis(double v, double u, double l)
	{
		if (v < -MINDOUBLE)
		{
			return INFINITY;
		}

		return -6 / (2 * v + 5);
	}
}