#include "empirical_distribution.h"

namespace distremp
{
	std::map<std::pair<double, double>, double> create_distribution(std::vector<double>& sample)
	{
		std::sort(sample.begin(), sample.end());
		std::map<std::pair<double, double>, double> result;

		size_t n = sample.size();
		size_t k = log(n) + 1;

		double delta = (sample[n - 1] - sample[0]) / k;
		double start_value = sample[0], end_value = sample[0] + delta;

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
}