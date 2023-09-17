#ifndef MIXTURE_DISTRIBUTION
#define MIXTURE_DISTRIBUTION

#include "main_distribution.h"

namespace distrmix
{
	double generate_value(double v1, double u1, double l1, double v2, double u2, double l2, double p);
	double get_density(double x, double v1, double u1, double l1, double v2, double u2, double l2, double p);
	double get_expected_value(double v1, double u1, double l1, double v2, double u2, double l2, double p);
	double get_dispersion(double v1, double u1, double l1, double v2, double u2, double l2, double p);
	double get_skewness(double v1, double u1, double l1, double v2, double u2, double l2, double p);
	double get_kurtosis(double v1, double u1, double l1, double v2, double u2, double l2, double p);
}

#endif