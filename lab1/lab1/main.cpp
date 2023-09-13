#include "main_distribution.h"
#include "mixture_distibution.h"
#include "empirical_distribution.h"
#include <iostream>

int main()
{
	srand(time(0));

	size_t n = 1000000;

	double v1 = 2;
	double u1 = 0;
	double l1 = 1;
	double v2 = 0.5;
	double u2 = 0;
	double l2 = 1;
	double p = 0.5;

	std::cout << distr::get_density(distr::get_expected_value(v1, u1, l1), v1, u1, l1) << "\n";
	std::cout << distr::get_expected_value(v1, u1, l1) << "\n";
	std::cout << distr::get_dispersion(v1, u1, l1) << "\n";
	std::cout << distr::get_skewness(v1, u1, l1) << "\n";
	std::cout << distr::get_kurtosis(v1, u1, l1) << "\n";

	std::vector<double> sample;
	sample.resize(n);
	for (size_t i = 0; i < n; i++)
	{
		sample[i] = distr::generate_value(v1, u1, l1);
	}

	std::map<std::pair<double, double>, double> emp_distr = distremp::create_distribution(sample);
	for (auto it = emp_distr.begin(); it != emp_distr.end(); it++)
	{
		std::cout << it->first.first << " " << it->first.second << " " << it->second << "\n";
	}

	return 0;
}