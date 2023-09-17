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

	bool emp_distribution();

	bool emp_distribution();
}