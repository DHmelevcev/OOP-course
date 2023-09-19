#include "tests.h"

#ifndef EPS
#define EPS 1e-3
#endif


namespace test
{
	bool main_distribution_density()
	{
		std::vector<double> v = { 0, 0.5, 1, 2, 3, 4, 5, 6, 7, 8 };
		double u = 0;
		double l = 1;
		std::vector<double> f = { 0.5, 0.637, 0.75, 0.938, 1.094, 1.23, 1.354, 1.466, 1.571, 1.669 };
		double x = 0;
		
		for (std::vector<double>::const_iterator itv = v.begin(), itf = f.begin(); itv != v.end() && itf != f.end(); itv++, itf++)
		{
			if (abs(distr::get_density(x, *itv, u, l) - *itf) > EPS)
			{
				return false;
			}
		}

		return true;
	}

	bool main_distribution_transforms()
	{
		std::vector<double> v = { 0, 0.5, 1, 2, 3, 4, 5, 6, 7, 8 };
		double u = rand() % 12 - 5;
		double l = 2;
		std::vector<double> f = { 0.5, 0.637, 0.75, 0.938, 1.094, 1.23, 1.354, 1.466, 1.571, 1.669 };
		double x = u;

		for (std::vector<double>::const_iterator itv = v.begin(), itf = f.begin(); itv != v.end() && itf != f.end(); itv++, itf++)
		{
			if (abs(distr::get_density(x, *itv, u, l) - *itf / l) > EPS)
			{
				return false;
			}
		}

		return true;
	}

	bool mix_distribution_density()
	{
		std::vector<double> v = { 0, 0.5, 1, 2, 3, 4, 5, 6, 7, 8 };
		double u1; do u1 = rand() % 12 - 5; while (!u1);
		double u2 = u1;
		double l1 = 2;
		double l2 = l1;
		double p = static_cast<double>(rand()) / RAND_MAX;
		double x = u1;

		for (std::vector<double>::const_iterator itv = v.begin(); itv != v.end(); itv++)
		{
			double fmix = (1 - p) * distr::get_density(x, *itv, u1, l1) + p * distr::get_density(x, *itv, u2, l2);

			if (abs(distrmix::get_density(u1, *itv, u1, l1, *itv, u2, l2, p) - fmix) > EPS)
			{
				return false;
			}
		}

		return true;
	}

	bool mix_distribution_expected_value()
	{
		double u1 = rand() % 12 - 5;
		double u2; do u2 = rand() % 12 - 5; while (u2 == u1);
		double l1; do l1 = static_cast<double>(rand()) * 4 / RAND_MAX; while (!l1);
		double l2; do l2 = static_cast<double>(rand()) * 4 / RAND_MAX; while (!l2);
		double v1 = static_cast<double>(rand()) * 4 / RAND_MAX;
		double v2 = static_cast<double>(rand()) * 4 / RAND_MAX;
		double p = 0.5;

		double expected_value = (1 - p) * distr::get_expected_value(v1, u1, l1) + p * distr::get_expected_value(v2, u2, l2);

		if (abs(distrmix::get_expected_value(v1, u1, l1, v2, u2, l2, p) - expected_value) > EPS)
		{
			return false;
		}

		return true;
	}

	bool mix_distribution_dispersion()
	{
		std::vector<double> v = { 0, 0.5, 1, 2, 3, 4, 5, 6, 7, 8 };
		double u1 = 0;
		double u2 = u1;
		double l1 = 1;
		double l2 = 3;
		double p = 0.5;

		for (std::vector<double>::const_iterator itv = v.begin(); itv != v.end(); itv++)
		{
			double dispersion = (1 - p) * (pow(distr::get_expected_value(*itv, u1, l1), 2) + distr::get_dispersion(*itv, u1, l1))
								+ p * (pow(distr::get_expected_value(*itv, u2, l2), 2) + distr::get_dispersion(*itv, u2, l2))
								- distrmix::get_expected_value(*itv, u1, l1, *itv, u2, l2, p);

			if (abs(distrmix::get_dispersion(*itv, u1, l1, *itv, u2, l2, p) - dispersion) > EPS)
			{
				return false;
			}
		}

		return true;
	}

	void emp_distribution()
	{
		std::cout << "====================================================\nEmpirical distribution test\n\n";

		size_t n1 = 100;
		size_t n2 = 10000;
		size_t n3 = 1000000;

		double v1 = 0.5;
		double u1 = 10;
		double l1 = 2;

		double v2 = 1;
		double u2 = 6;
		double l2 = 1;
		double p = 0.4;

		std::vector<double> x = { 4, 4.5, 5.1, 5.5, 6, 6.5, 6.9, 7.5, 8.1, 8.5, 9, 9.5, 10, 10.5, 11, 11.5, 11.9, 12.5, 13 };

		std::cout << "Main distribution:\n";

		std::cout << "Theoretical expected value: " << distr::get_expected_value(v1, u1, l1) << "\n";
		std::cout << "Theoretical dispersion:     " << distr::get_dispersion(v1, u1, l1) << "\n";
		std::cout << "Theoretical skewness:       " << distr::get_skewness(v1, u1, l1) << "\n";
		std::cout << "Theoretical kurtosis:       " << distr::get_kurtosis(v1, u1, l1) << "\n\n";

		std::vector<double> sample1;
		sample1.resize(n1);
		for (size_t i = 0; i < n1; i++)
		{
			sample1[i] = distr::generate_value(v1, u1, l1);
		}
		std::map<std::pair<double, double>, double> emp_distr1 = distremp::create_distribution(sample1);

		std::cout << "N = " << n1 << "\n";
		std::cout << "Empirical expected value:   " << distremp::get_expected_value(sample1) << "\n";
		std::cout << "Empirical dispersion:       " << distremp::get_dispersion(sample1) << "\n";
		std::cout << "Empirical skewness:         " << distremp::get_skewness(sample1) << "\n";
		std::cout << "Empirical kurtosis:         " << distremp::get_kurtosis(sample1) << "\n\n";

		std::vector<double> sample2;
		sample2.resize(n2);
		for (size_t i = 0; i < n2; i++)
		{
			sample2[i] = distr::generate_value(v1, u1, l1);
		}
		std::map<std::pair<double, double>, double> emp_distr2 = distremp::create_distribution(sample2);

		std::cout << "N = " << n2 << "\n";
		std::cout << "Empirical expected value:   " << distremp::get_expected_value(sample2) << "\n";
		std::cout << "Empirical dispersion:       " << distremp::get_dispersion(sample2) << "\n";
		std::cout << "Empirical skewness:         " << distremp::get_skewness(sample2) << "\n";
		std::cout << "Empirical kurtosis:         " << distremp::get_kurtosis(sample2) << "\n\n";

		std::vector<double> sample3;
		sample3.resize(n3);
		for (size_t i = 0; i < n3; i++)
		{
			sample3[i] = distr::generate_value(v1, u1, l1);
		}
		std::map<std::pair<double, double>, double> emp_distr3 = distremp::create_distribution(sample3);

		std::cout << "N = " << n3 << "\n";
		std::cout << "Empirical expected value:  " << distremp::get_expected_value(sample3) << "\n";
		std::cout << "Empirical dispersion:      " << distremp::get_dispersion(sample3) << "\n";
		std::cout << "Empirical skewness:        " << distremp::get_skewness(sample3) << "\n";
		std::cout << "Empirical kurtosis:        " << distremp::get_kurtosis(sample3) << "\n\n";

		std::cout << "Density:     Theoretical" 
			<< "  N =" << std::setw(8) << n1 
			<< "  N =" << std::setw(8) << n2 
			<< "  N =" << std::setw(8) << n3 << "\n";
		for (std::vector<double>::const_iterator it = x.begin(); it != x.end(); it++)
		{
			std::cout << "x =" << std::setw(8) << *it 
				<< std::setw(13) << distr::get_density(*it, v1, u1, l1) 
				<< std::setw(13) << distremp::get_density(emp_distr1, *it)
				<< std::setw(13) << distremp::get_density(emp_distr2, *it) 
				<< std::setw(13) << distremp::get_density(emp_distr3, *it) << "\n";
		}

		std::cout << "----------------------------------------------------\nMixed distribution:\n";

		std::cout << "Theoretical expected value: " << distrmix::get_expected_value(v1, u1, l1, v2, u2, l2, p) << "\n";
		std::cout << "Theoretical dispersion:     " << distrmix::get_dispersion(v1, u1, l1, v2, u2, l2, p) << "\n";
		std::cout << "Theoretical skewness:       " << distrmix::get_skewness(v1, u1, l1, v2, u2, l2, p) << "\n";
		std::cout << "Theoretical kurtosis:       " << distrmix::get_kurtosis(v1, u1, l1, v2, u2, l2, p) << "\n\n";

		for (size_t i = 0; i < n1; i++)
		{
			sample1[i] = distrmix::generate_value(v1, u1, l1, v2, u2, l2, p);
		}
		emp_distr1 = distremp::create_distribution(sample1);

		std::cout << "N = " << n1 << "\n";
		std::cout << "Empirical expected value:   " << distremp::get_expected_value(sample1) << "\n";
		std::cout << "Empirical dispersion:       " << distremp::get_dispersion(sample1) << "\n";
		std::cout << "Empirical skewness:         " << distremp::get_skewness(sample1) << "\n";
		std::cout << "Empirical kurtosis:         " << distremp::get_kurtosis(sample1) << "\n\n";

		for (size_t i = 0; i < n2; i++)
		{
			sample2[i] = distrmix::generate_value(v1, u1, l1, v2, u2, l2, p);
		}
		emp_distr2 = distremp::create_distribution(sample2);

		std::cout << "N = " << n2 << "\n";
		std::cout << "Empirical expected value:   " << distremp::get_expected_value(sample2) << "\n";
		std::cout << "Empirical dispersion:       " << distremp::get_dispersion(sample2) << "\n";
		std::cout << "Empirical skewness:         " << distremp::get_skewness(sample2) << "\n";
		std::cout << "Empirical kurtosis:         " << distremp::get_kurtosis(sample2) << "\n\n";

		for (size_t i = 0; i < n3; i++)
		{
			sample3[i] = distrmix::generate_value(v1, u1, l1, v2, u2, l2, p);
		}
		emp_distr3 = distremp::create_distribution(sample3);

		std::cout << "N = " << n3 << "\n";
		std::cout << "Empirical expected value:  " << distremp::get_expected_value(sample3) << "\n";
		std::cout << "Empirical dispersion:      " << distremp::get_dispersion(sample3) << "\n";
		std::cout << "Empirical skewness:        " << distremp::get_skewness(sample3) << "\n";
		std::cout << "Empirical kurtosis:        " << distremp::get_kurtosis(sample3) << "\n\n";

		std::cout << "Density:     Theoretical" 
			<< "  N =" << std::setw(8) << n1 
			<< "  N =" << std::setw(8) << n2 
			<< "  N =" << std::setw(8) << n3 << "\n";
		for (std::vector<double>::const_iterator it = x.begin(); it != x.end(); it++)
		{
			std::cout << "x =" << std::setw(8) << *it 
				<< std::setw(13) << distrmix::get_density(*it, v1, u1, l1, v2, u2, l2, p) 
				<< std::setw(13) << distremp::get_density(emp_distr1, *it)
				<< std::setw(13) << distremp::get_density(emp_distr2, *it) 
				<< std::setw(13) << distremp::get_density(emp_distr3, *it) << "\n";
		}

		std::cout << "----------------------------------------------------\nEmpirical distribution:\n";

		for (size_t i = 0; i < n3; i++)
		{
			sample3[i] = distr::generate_value(v1, u1, l1);
		}
		emp_distr3 = distremp::create_distribution(sample3);

		std::cout << "Theoretical expected value:           " << distr::get_expected_value(v1, u1, l1) << "\n";
		std::cout << "Theoretical dispersion:               " << distr::get_dispersion(v1, u1, l1) << "\n";
		std::cout << "Theoretical skewness:                 " << distr::get_skewness(v1, u1, l1) << "\n";
		std::cout << "Theoretical kurtosis:                 " << distr::get_kurtosis(v1, u1, l1) << "\n\n";

		std::cout << "N = " << n3 << "\n";
		std::cout << "Empirical 1st stage expected value:   " << distremp::get_expected_value(sample3) << "\n";
		std::cout << "Empirical 1st stage dispersion:       " << distremp::get_dispersion(sample3) << "\n";
		std::cout << "Empirical 1st stage skewness:         " << distremp::get_skewness(sample3) << "\n";
		std::cout << "Empirical 1st stage kurtosis:         " << distremp::get_kurtosis(sample3) << "\n\n";

		std::vector<double> sample4;
		sample4.resize(n3);
		for (size_t i = 0; i < n3; i++)
		{
			double p = static_cast<double>(rand()) / RAND_MAX;

			auto it = emp_distr3.begin();
			do {
				p -= it->second * (it->first.second - it->first.first); it++;
			} while (p > 1e-7);
			it--;

			sample4[i] = static_cast<double>(rand()) / RAND_MAX * (it->first.second - it->first.first) + it->first.first;
		}
		std::map<std::pair<double, double>, double> emp_distr4 = distremp::create_distribution(sample4);

		std::cout << "Empirical 2nd stage expected value:   " << distremp::get_expected_value(sample4) << "\n";
		std::cout << "Empirical 2nd stage dispersion:       " << distremp::get_dispersion(sample4) << "\n";
		std::cout << "Empirical 2nd stage skewness:         " << distremp::get_skewness(sample4) << "\n";
		std::cout << "Empirical 2nd stage kurtosis:         " << distremp::get_kurtosis(sample4) << "\n\n";

		std::cout << "Density:     Theoretical  Empirical 1st stage  Empirical 2nd stage\n";
		for (auto it = emp_distr3.begin(); it != emp_distr3.end(); it++)
		{
			double x = (it->first.second + it->first.first) / 2;
			std::cout << "x =" << std::setw(8) << x 
				<< std::setw(13) << distr::get_density(x, v1, u1, l1)
				<< std::setw(21) << distremp::get_density(emp_distr3, x)
				<< std::setw(21) << distremp::get_density(emp_distr4, x) << "\n";
		}

		std::cout << "====================================================\n\n";

		return;
	}
}