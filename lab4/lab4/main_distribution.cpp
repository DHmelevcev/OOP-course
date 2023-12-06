#include "main_distribution.h"

#ifndef PI
#define PI 3.14159265359
#endif

#ifndef EPS
#define EPS 1e-7
#endif

MainDistribution::MainDistribution() noexcept : _v(0), _u(0), _l(1) {}

MainDistribution::MainDistribution(const double v, const double u, const double l) :
	_v(v < 0 ? throw std::string("Value error: v can't be neagative") : v),
	_u(u),
	_l(l < EPS ? throw std::string("Value error: l must be positive") : l) {}

MainDistribution::MainDistribution(const std::string file_name)
{
	load_from_file(file_name);
}

void MainDistribution::set_v(const double v)
{
	if (v < 0)
	{
		throw std::string("Value error: v can't be neagative");
	}

	_v = v;
}
void MainDistribution::set_u(const double u)
{
	_u = u;
}
void MainDistribution::set_l(const double l)
{
	if (l < EPS)
	{
		throw std::string("Value error: l must be positive");
	}

	_l = l;
}

double MainDistribution::generate_value() const
{
	double r1 = static_cast<double>(rand()) / RAND_MAX;
	double r2 = static_cast<double>(rand()) / RAND_MAX;

	return _u + _l * sqrt(1 - pow(r1, 1 / (_v + 0.5))) * cos(2 * PI * r2);
}

double MainDistribution::get_density(const double x) const
{
	if ((x - _u) / _l < -1 || (x - _u) / _l > 1)
	{
		return 0;
	}

	return pow((1 - pow((x - _u) / _l, 2)) / 4, _v) / (2 * beta(_v + 1, _v + 1) * _l);
}

double MainDistribution::get_expected_value() const
{
	return get_u();
}

double MainDistribution::get_dispersion() const
{
	return pow(_l, 2) / (2 * _v + 3);
}

double MainDistribution::get_skewness() const
{
	return 0;
}

double MainDistribution::get_kurtosis() const
{
	return -6 / (2 * _v + 5);
}

void MainDistribution::save_to_file(const std::string file_name) const
{
	std::ofstream file(file_name + ".distr");

	file << _v << '\n';
	file << _u << '\n';
	file << _l;

	file.close();
}

void MainDistribution::load_from_file(const std::string file_name)
{
	std::ifstream file(file_name + ".distr");
	if (!file)
	{
		throw std::string("Save file for MainDistribution not found");
	}

	double v = 0, u = 0, l = 1;

	file >> v;
	file >> u;
	file >> l;

	if (!file)
	{
		file.close();
		throw std::string("Save file broken");
	}
	file.close();

	if (v < 0)
	{
		throw std::string("Value error: v can't be neagative");
	}

	if (l < EPS)
	{
		throw std::string("Value error: l must be positive");
	}

	_v = v;
	_u = u;
	_l = l;
}