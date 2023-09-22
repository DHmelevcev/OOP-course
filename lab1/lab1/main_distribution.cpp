#include "main_distribution.h"

#ifndef PI
#define PI 3.14159265359
#endif

namespace distr
{
	double generate_value(double v, double u, double l)
	{
		if (v < 0)
		{
			throw;
		}

		double r1 = static_cast<double>(rand()) / RAND_MAX;
		double r2 = static_cast<double>(rand()) / RAND_MAX;

		return u + l * sqrt(1 - pow(r1, 1 / (v + 0.5))) * cos(2 * PI * r2);
	}

	double get_density(double x, double v, double u, double l)
	{
		if (v < 0)
		{
			throw;
		}

		if ((x - u) / l < -1 || (x - u) / l > 1)
		{
			return 0;
		}

		double result = pow((1 - pow((x - u) / l, 2)) / 4, v) / (2 * beta(v + 1, v + 1) * l);

		return result;
	}

	double get_expected_value(double v, double u, double l)
	{
		if (v < 0)
		{
			throw;
		}

		return u;
	}

	double get_dispersion(double v, double u, double l)
	{
		if (v < 0)
		{
			throw;
		}

		return pow(l, 2) / (2 * v + 3);
	}

	double get_skewness(double v, double u, double l)
	{
		if (v < 0)
		{
			throw;
		}

		return 0;
	}

	double get_kurtosis(double v, double u, double l)
	{
		if (v < 0)
		{
			throw;
		}

		return -6 / (2 * v + 5);
	}
}