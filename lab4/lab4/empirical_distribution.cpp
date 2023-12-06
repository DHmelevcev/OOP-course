#include "empirical_distribution.h"
#include "iostream"

#ifndef MINDOUBLE
#define MINDOUBLE 1e-15
#endif

EmpiricalDistribution::EmpiricalDistribution(const size_t n, const IDistribution& distr, size_t k) :
	_n(n > 1 ? n : throw std::string("Value error: n must be larger than 1")),
	_k(k > 1 ? k : static_cast<size_t>(log(static_cast<double>(_n)) / log(2.)) + 1),
	_sample(new double[_n]),
	_freq(new double[_k])
{
	for (size_t i = 0; i < _n; ++i)
	{
		_sample[i] = distr.generate_value();
	}

	calculate_distribution();
}

EmpiricalDistribution::EmpiricalDistribution(const std::string file_name) :
	_n(0),
	_sample()
{
	load_from_file(file_name);
}

EmpiricalDistribution::EmpiricalDistribution(const EmpiricalDistribution& empirical_distr)  noexcept :
	_n(empirical_distr._n),
	_k(empirical_distr._k),
	_sample(new double[_n]),
	_freq(new double[_k])
{
	for (size_t i = 0; i < _n; ++i)
	{
		_sample[i] = empirical_distr._sample[i];
	}

	for (size_t i = 0; i < _k; ++i)
	{
		_freq[i] = empirical_distr._freq[i];
	}

	_start = empirical_distr._start;
	_delta = empirical_distr._delta;
}

EmpiricalDistribution& EmpiricalDistribution::operator=(const EmpiricalDistribution& empirical_distr)
{
	if (this == &empirical_distr)
	{
		return *this;
	}

	delete[] _sample;
	delete[] _freq;
	_n = empirical_distr._n;
	_k = empirical_distr._k;
	_sample = new double[_n];
	_freq = new double[_k];

	for (size_t i = 0; i < _n; ++i)
	{
		_sample[i] = empirical_distr._sample[i];
	}

	for (size_t i = 0; i < _k; ++i)
	{
		_freq[i] = empirical_distr._freq[i];
	}

	_start = empirical_distr._start;
	_delta = empirical_distr._delta;

	return *this;
}

std::pair<std::pair<double, double>, double> EmpiricalDistribution::get_interval(const size_t k) const
{
	if (k > _k)
	{
		throw std::string("Value error: k index out of range");
	}

	double start = _start;
	size_t interval = k;
	while (interval) {
		start += _delta;
		interval--;
	}

	return std::pair<std::pair<double, double>, double>(std::pair<double, double>(start, start + _delta), _freq[k]);
}

void EmpiricalDistribution::set_k(const size_t k)
{
	_k = k > 1 ? k : static_cast<size_t>(log(static_cast<double>(_n)) / log(2.)) + 1;
	delete[] _freq;
	_freq = new double[_k];
	calculate_distribution();
}

double EmpiricalDistribution::generate_value() const
{
	double p = static_cast<double>(rand()) / RAND_MAX;

	auto it = _freq;
	double start = _start;
	do {
		p -= *it * _delta;
		start += _delta;
		it++;
	} while (p > 1e-7);
	it--;

	return -static_cast<double>(rand()) / RAND_MAX * _delta + start;
}

double EmpiricalDistribution::get_density(const double x) const
{
	if (x < _start || x > _start + _k * _delta)
	{
		return 0;
	}

	size_t k = static_cast<double>((x - _start) / _delta);

	return _freq[k];
}

double EmpiricalDistribution::get_expected_value() const
{
	double result = 0;

	for (auto it = _sample; it < _sample + _n; ++it)
	{
		result += *it;
	}

	return result / _n;
}

double EmpiricalDistribution::get_dispersion() const
{
	double result = 0;
	double expected_value = get_expected_value();

	for (auto it = _sample; it < _sample + _n; ++it)
	{
		result += pow(*it - expected_value, 2);
	}

	return result / _n;
}

double EmpiricalDistribution::get_skewness() const
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

double EmpiricalDistribution::get_kurtosis() const
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
	std::ofstream file(file_name + ".distre");

	file << _n;

	for (auto it = _sample; it < _sample + _n; ++it)
	{
		file << '\n' << *it;
	}

	file.close();
}

void EmpiricalDistribution::load_from_file(const std::string file_name)
{
	std::ifstream file(file_name + ".distre");
	if (!file)
	{
		throw std::string("Save file for EmpiricalDistribution not found");
	}

	double n;

	file >> n;

	if (n < 2)
	{
		throw std::string("Value error : n must be larger than 1");
	}

	delete[] _sample;
	_sample = new double[n];

	for (size_t i = 0; i < n; ++i)
	{
		file >> _sample[i];
	}

	if (!file)
	{
		file.close();
		delete[] _sample;
		throw std::string("Save file broken");
	}
	file.close();

	_n = n;
	delete[] _freq;
	_k = static_cast<size_t>(log(static_cast<double>(_n)) / log(2.)) + 1;
	_freq = new double[_k];
	calculate_distribution();
}

EmpiricalDistribution::~EmpiricalDistribution()
{
	delete[] _sample;
	delete[] _freq;
}

void EmpiricalDistribution::calculate_distribution()
{
	std::sort(_sample, _sample + _n, std::less<double>{});

	_delta = (_sample[_n - 1] - _sample[0]) / (_k - 1);
	if (isnan(_delta) || _delta < MINDOUBLE)
	{
		_k = 1;
		_delta = 1;
	}
	_start = _sample[0] - 0.5 * _delta;
	double end = _start + _delta;

	auto it = _sample;
	double count = 0;

	for (size_t i = 0; i < _k - 1; ++i)
	{
		while (*it < end)
		{
			count++;
			it++;
		}

		_freq[i] = count / _n / _delta;
		end += _delta;
		count = 0;
	}

	while (it != _sample + _n)
	{
		count++;
		it++;
	}

	_freq[_k - 1] = count / _n / _delta;
}