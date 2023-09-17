#ifndef EMPIRICAL_DISTRIBUTION
#define EMPIRICAL_DISTRIBUTION

#include <vector>
#include <algorithm>
#include <map>

namespace distremp
{
	std::map<std::pair<double, double>, double> create_distribution(std::vector<double> sample);
	double get_density(std::map<std::pair<double, double>, double>& distribution, double x);
	double get_density(std::vector<double>& sample, double x);
	double get_expected_value(std::vector<double>& sample);
	double get_dispersion(std::vector<double>& sample);
	double get_skewness(std::vector<double>& sample);
	double get_kurtosis(std::vector<double>& sample);
}

#endif