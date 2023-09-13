#ifndef MAIN_DISTRIBUTION
#define MAIN_DISTRIBUTION

#include "spec_func.hpp"
#include <cstdlib>
#include <time.h>

namespace distr
{
	double generate_value(double v, double u = 0, double l = 1);
	double get_density(double x, double v, double u = 0, double l = 1);
	double get_expected_value(double v, double u = 0, double l = 1);
	double get_dispersion(double v, double u = 0, double l = 1);
	double get_skewness(double v, double u = 0, double l = 1);
	double get_kurtosis(double v, double u = 0, double l = 1);
}

#endif