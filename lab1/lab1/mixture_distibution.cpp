#include "mixture_distibution.h"

namespace distrmix
{
	double generate_value(double v1, double u1, double l1, double v2, double u2, double l2, double p)
	{
		if (v1 < 0 || v2 < 0 || p < 0 && p > 1)
		{
			throw;
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

	double get_density(double x, double v1, double u1, double l1, double v2, double u2, double l2, double p)
	{
		if (v1 < 0 || v2 < 0 || p < 0 && p > 1)
		{
			throw;
		}

		return (1 - p) * distr::get_density(x, v1, u1, l1) + p * distr::get_density(x, v2, u2, l2);
	}

	double get_expected_value(double v1, double u1, double l1, double v2, double u2, double l2, double p)
	{
		if (v1 < 0 || v2 < 0 || p < 0 && p > 1)
		{
			throw;
		}

		return (1 - p) * distr::get_expected_value(v1, u1, l1) + p * distr::get_expected_value(v2, u2, l2);
	}

	double get_dispersion(double v1, double u1, double l1, double v2, double u2, double l2, double p)
	{
		if (v1 < 0 || v2 < 0 || p < 0 && p > 1)
		{
			throw;
		}

		double mix_expected_value = distrmix::get_expected_value(v1, u1, l1, v2, u2, l2, p);
		double expected_value1 = distr::get_expected_value(v1, u1, l1);
		double expected_value2 = distr::get_expected_value(v2, u2, l2);
		double dispersion1 = distr::get_dispersion(v1, u1, l1);
		double dispersion2 = distr::get_dispersion(v2, u2, l2);

		return	(1 - p) * (pow(expected_value1, 2) + dispersion1)
				+ p * (pow(expected_value2, 2) + dispersion2)
				- pow(mix_expected_value, 2);
	}

	double get_skewness(double v1, double u1, double l1, double v2, double u2, double l2, double p)
	{
		if (v1 < 0 || v2 < 0 || p < 0 && p > 1)
		{
			throw;
		}

		double mix_expected_value = distrmix::get_expected_value(v1, u1, l1, v2, u2, l2, p);
		double mix_dispersion = distrmix::get_dispersion(v1, u1, l1, v2, u2, l2, p);
		double expected_value1 = distr::get_expected_value(v1, u1, l1);
		double expected_value2 = distr::get_expected_value(v2, u2, l2);
		double dispersion1 = distr::get_dispersion(v1, u1, l1);
		double dispersion2 = distr::get_dispersion(v2, u2, l2);
		double skewness1 = distr::get_skewness(v1, u1, l1);
		double skewness2 = distr::get_skewness(v2, u2, l2);

		return	((1 - p) * (pow(expected_value1 - mix_expected_value, 3) + 3 * (expected_value1 - mix_expected_value)
					* dispersion1 + pow(dispersion1, 1.5) * skewness1)
				+ p * (pow(expected_value2 - mix_expected_value, 3) + 3 * (expected_value2 - mix_expected_value)
					* dispersion2 + pow(dispersion2, 1.5) * skewness2))
				/ pow(mix_dispersion, 1.5);
	}

	double get_kurtosis(double v1, double u1, double l1, double v2, double u2, double l2, double p)
	{
		if (v1 < 0 || v2 < 0 || p < 0 && p > 1)
		{
			throw;
		}

		double mix_expected_value = distrmix::get_expected_value(v1, u1, l1, v2, u2, l2, p);
		double mix_dispersion = distrmix::get_dispersion(v1, u1, l1, v2, u2, l2, p);
		double expected_value1 = distr::get_expected_value(v1, u1, l1);
		double expected_value2 = distr::get_expected_value(v2, u2, l2);
		double dispersion1 = distr::get_dispersion(v1, u1, l1);
		double dispersion2 = distr::get_dispersion(v2, u2, l2);
		double skewness1 = distr::get_skewness(v1, u1, l1);
		double skewness2 = distr::get_skewness(v2, u2, l2);
		double kurtosis1 = distr::get_kurtosis(v1, u1, l1);
		double kurtosis2 = distr::get_kurtosis(v2, u2, l2);

		return	((1 - p) * (pow(expected_value1 - mix_expected_value, 4) + 6 * pow(expected_value1 - mix_expected_value, 2)
				* dispersion1 + 4 * (expected_value1 - mix_expected_value) * pow(dispersion1, 1.5) * skewness1
				+ pow(dispersion1, 2) * (kurtosis1 + 3))
			+ p * (pow(expected_value2 - mix_expected_value, 4) + 6 * pow(expected_value2 - mix_expected_value, 2)
				* dispersion2 + 4 * (expected_value2 - mix_expected_value) * pow(dispersion2, 1.5) * skewness2
				+ pow(dispersion2, 2) * (kurtosis2 + 3)))
			/ pow(mix_dispersion, 2) - 3;
	}
}