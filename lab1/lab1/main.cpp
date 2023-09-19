#include "main_distribution.h"
#include "mixture_distibution.h"
#include "empirical_distribution.h"
#include "tests.h"
#include <iostream>

int main()
{
	srand(time(0));

	//size_t n = 100000;

	//double v1 = 10;
	//double u1 = 0;
	//double l1 = 1;
	//double v2 = 1;
	//double u2 = 9;
	//double l2 = 1;
	//double p = 0.5;

	//std::cout << distr::get_density(distr::get_expected_value(v1, u1, l1), v1, u1, l1) << "\n";
	//std::cout << distr::get_expected_value(v1, u1, l1) << "\n";
	//std::cout << distr::get_dispersion(v1, u1, l1) << "\n";
	//std::cout << distr::get_skewness(v1, u1, l1) << "\n";
	//std::cout << distr::get_kurtosis(v1, u1, l1) << "\n\n";

	//std::cout << distr::get_density(distr::get_expected_value(v2, u2, l2), v2, u2, l2) << "\n";
	//std::cout << distr::get_expected_value(v2, u2, l2) << "\n";
	//std::cout << distr::get_dispersion(v2, u2, l2) << "\n";
	//std::cout << distr::get_skewness(v2, u2, l2) << "\n";
	//std::cout << distr::get_kurtosis(v2, u2, l2) << "\n\n";

	//std::cout << distrmix::get_density(0, v1, u1, l1, v2, u2, l2, p) << "\n";
	//std::cout << distrmix::get_expected_value(v1, u1, l1, v2, u2, l2, p) << "\n";
	//std::cout << distrmix::get_dispersion(v1, u1, l1, v2, u2, l2, p) << "\n";
	//std::cout << distrmix::get_skewness(v1, u1, l1, v2, u2, l2, p) << "\n";
	//std::cout << distrmix::get_kurtosis(v1, u1, l1, v2, u2, l2, p) << "\n\n";

	//std::vector<double> sample;
	//sample.resize(n);
	//for (size_t i = 0; i < n; i++)
	//{
	//	sample[i] = distr::generate_value(v1, u1, l1);
	//}

	//std::map<std::pair<double, double>, double> emp_distr = distremp::create_distribution(sample);
	//for (auto it = emp_distr.begin(); it != emp_distr.end(); it++)
	//{
	//	std::cout << it->first.first << " " << it->first.second << " " << it->second << "\n";
	//}

	//std::cout << "\n" << distremp::get_density(emp_distr, distr::get_expected_value(v1, u1, l1)) << "\n";
	//std::cout << distremp::get_expected_value(sample) << "\n";
	//std::cout << distremp::get_dispersion(sample) << "\n";
	//std::cout << distremp::get_skewness(sample) << "\n";
	//std::cout << distremp::get_kurtosis(sample) << "\n\n";

	std::cout << test::main_distribution_density() << "\n";
	std::cout << test::main_distribution_transforms() << "\n\n";
	std::cout << test::mix_distribution_density() << "\n";
	std::cout << test::mix_distribution_expected_value() << "\n";
	std::cout << test::mix_distribution_dispersion() << "\n\n";

	test::emp_distribution();

	return 0;
}