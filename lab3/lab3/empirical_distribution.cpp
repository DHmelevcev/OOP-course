#include "empirical_distribution.h"
#include "iostream"

#ifndef MINDOUBLE
#define MINDOUBLE 1e-15
#endif

EmpiricalDistribution::EmpiricalDistribution(size_t n, const MainDistribution& main_distr, size_t k) :
	_n(n > 1 ? n : throw std::string("Value error: n must be larger than 1")),
	_sample(new double[_n])
{
	for (size_t i = 0; i < _n; ++i)
	{
		_sample[i] = main_distr.generate_value();
	}

	calculate_distribution(k);
}

EmpiricalDistribution::EmpiricalDistribution(size_t n, const MixedDistribution& mixed_distr, size_t k) :
	_n(n > 1 ? n : throw std::string("Value error: n must be larger than 1")),
	_sample(new double[_n])
{
	for (size_t i = 0; i < _n; ++i)
	{
		_sample[i] = mixed_distr.generate_value();
	}

	calculate_distribution(k);
}

EmpiricalDistribution::EmpiricalDistribution(size_t n, const EmpiricalDistribution& empirical_distr, size_t k) :
	_n(n > 1 ? n : throw std::string("Value error: n must be larger than 1")),
	_sample(new double[_n])
{
	for (size_t i = 0; i < _n; ++i)
	{
		_sample[i] = empirical_distr.generate_value();
	}

	calculate_distribution(k);
}

EmpiricalDistribution::EmpiricalDistribution(const EmpiricalDistribution& empirical_distr)  noexcept :
	_n(empirical_distr._n),
	_sample(new double[_n])
{
	for (size_t i = 0; i < _n; ++i)
	{
		_sample[i] = empirical_distr._sample[i];
	}

	_freq = empirical_distr._freq;
}

EmpiricalDistribution& EmpiricalDistribution::operator=(const EmpiricalDistribution& empirical_distr)
{
	if (this == &empirical_distr)
	{
		return *this;
	}

	delete[] _sample;
	_n = empirical_distr._n;
	_sample = new double[_n];

	for (size_t i = 0; i < _n; ++i)
	{
		_sample[i] = empirical_distr._sample[i];
	}

	_freq = empirical_distr._freq;
}

std::pair<std::pair<double, double>, double> EmpiricalDistribution::get_interval(size_t k) const
{
	if (k > get_k())
	{
		throw std::string("Value error: k index out of range");
	}
	auto interval = _freq.begin();
	while (k) {
		interval++;
		k--;
	}

	return *interval;
}

void EmpiricalDistribution::set_k(size_t k)
{
	_freq.clear();
	calculate_distribution(k);
}

double EmpiricalDistribution::generate_value() const
{
	double p = static_cast<double>(rand()) / RAND_MAX;

	auto it = _freq.begin();
	do {
		p -= it->second * (it->first.second - it->first.first); it++;
	} while (p > 1e-7);
	it--;

	return static_cast<double>(rand()) / RAND_MAX * (it->first.second - it->first.first) + it->first.first;
}

double EmpiricalDistribution::get_density(double x) const
{
	if (x < _freq.begin()->first.first || x > _freq.rbegin()->first.second)
	{
		return 0;
	}

	for (auto it = _freq.begin(); it != _freq.end(); it++)
	{
		if (x < it->first.second)
		{
			return it->second;
		}
	}

	return _freq.rbegin()->second;
}

double EmpiricalDistribution::get_expected_value()
{
	double result = 0;

	for (auto it = _sample; it < _sample + _n; ++it)
	{
		result += *it;
	}

	return result / _n;
}

double EmpiricalDistribution::get_dispersion()
{
	double result = 0;
	double expected_value = get_expected_value();

	for (auto it = _sample; it < _sample + _n; ++it)
	{
		result += pow(*it - expected_value, 2);
	}

	return result / _n;
}

double EmpiricalDistribution::get_skewness()
{
	double expected_value = get_expected_value();
	double dispersion = get_dispersion();

	double result = 0;

	for (auto it = _sample; it < _sample + _n; ++it)
	{
		result += pow(*it - expected_value, 3);
	}

	return result / _n / pow(dispersion, 1.5);
}

double EmpiricalDistribution::get_kurtosis()
{
	double expected_value = get_expected_value();
	double dispersion = get_dispersion();

	double result = 0;

	for (auto it = _sample; it < _sample + _n; ++it)
	{
		result += pow(*it - expected_value, 4);
	}

	return result / _n / pow(dispersion, 2) - 3;
}

void EmpiricalDistribution::save_to_file(std::string file_name) const
{
	std::ofstream file(file_name);

	file.close();
}

void EmpiricalDistribution::load_from_file(std::string file_name)
{
	std::ifstream file(file_name);
	if (!file)
	{
		throw std::string("Save file for EmpiricalDistribution not found");
	}
}

EmpiricalDistribution::~EmpiricalDistribution()
{
	delete[] _sample;
}

void EmpiricalDistribution::calculate_distribution(size_t k)
{
	std::sort(_sample, _sample + _n, std::less<double>{});

	size_t _k = k > 1 ? k : static_cast<size_t>(log(static_cast<double>(_n)) / log(2.)) + 1;
	double delta = (_sample[_n - 1] - _sample[0]) / (_k - 1);
	if (isnan(delta) || delta < MINDOUBLE)
	{
		_k = 1;
		delta = 1;
	}
	double start_value = _sample[0] - 0.5 * delta, end_value = start_value + delta;

	auto it = _sample;
	double count = 0;

	for (size_t i = 0; i < _k - 1; ++i)
	{
		while (*it < end_value)
		{
			count++;
			it++;
		}

		_freq.insert(std::make_pair<std::pair<double, double>, double>(std::pair<double, double>(start_value, end_value), count / _n / delta));
		start_value = end_value;
		end_value += delta;
		count = 0;
	}

	while (it != _sample + _n)
	{
		count++;
		it++;
	}

	_freq.insert(std::make_pair<std::pair<double, double>, double>(std::pair<double, double>(start_value, end_value), count / _n / delta));
}