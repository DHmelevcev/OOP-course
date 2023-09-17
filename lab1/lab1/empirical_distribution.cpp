#include "empirical_distribution.h"

#ifndef MINDOUBLE
#define MINDOUBLE 1e-15
#endif

namespace distremp
{
	std::map<std::pair<double, double>, double> create_distribution(std::vector<double> sample)
	{
		if (sample.empty())
		{
			throw;
		}

		std::sort(sample.begin(), sample.end());
		std::map<std::pair<double, double>, double> result;

		size_t n = sample.size();
		size_t k = n < 3? n : log(n) + 1;

		double delta = (sample[n - 1] - sample[0]) / (k - 1);
		if (isnan(delta) || delta < MINDOUBLE)
		{
			k = 1;
			delta = 1;
		}
		double start_value = sample[0] - 0.5 * delta, end_value = start_value + delta;

		std::vector<double>::const_iterator it = sample.begin();
		double count = 0;

		for (size_t i = 0; i < k - 1; i++)
		{
			while (*it < end_value)
			{
				count++;
				it++;
			}

			result.insert(std::make_pair<std::pair<double, double>, double>(std::pair<double, double>(start_value, end_value), count / n / delta));
			start_value = end_value;
			end_value += delta;
			count = 0;
		}

		while (it != sample.end())
		{
			count++;
			it++;
		}

		result.insert(std::make_pair<std::pair<double, double>, double>(std::pair<double, double>(start_value, end_value), count / n / delta));

		return result;
	}

	double get_density(std::map<std::pair<double, double>, double>& distribution, double x)
	{
		if (x < distribution.begin()->first.first)
		{
			return 0;
		}

		for (auto it = distribution.begin(); it != distribution.end(); it++)
		{
			if (x < it->first.second)
			{
				return it->second;
			}
		}

		return 0;
	}

	double get_density(std::vector<double>& sample, double x)
	{
		auto distribution = distremp::create_distribution(sample);

		return get_density(distribution, x);
	}

	double get_expected_value(std::vector<double>& sample)
	{
		if (sample.empty())
		{
			throw;
		}

		double result = 0;

		for (auto it = sample.begin(); it < sample.end(); it++)
		{
			result += *it;
		}

		return result / sample.size();
	}

	double get_dispersion(std::vector<double>& sample)
	{
		double expected_value = get_expected_value(sample);

		double result = 0;

		for (auto it = sample.begin(); it < sample.end(); it++)
		{
			result += pow(*it - expected_value, 2);
		}

		return result / sample.size();
	}

	double get_skewness(std::vector<double>& sample)
	{
		double expected_value = get_expected_value(sample);
		double dispersion = get_dispersion(sample);

		double result = 0;

		for (auto it = sample.begin(); it < sample.end(); it++)
		{
			result += pow(*it - expected_value, 3);
		}

		return result / sample.size() / pow(dispersion, 1.5);
	}

	double get_kurtosis(std::vector<double>& sample)
	{
		double expected_value = get_expected_value(sample);
		double dispersion = get_dispersion(sample);

		double result = 0;

		for (auto it = sample.begin(); it < sample.end(); it++)
		{
			result += pow(*it - expected_value, 4);
		}

		return result / sample.size() / pow(dispersion, 2) - 3;
	}
}