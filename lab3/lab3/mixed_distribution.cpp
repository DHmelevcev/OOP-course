#include "mixed_distribution.h"

#ifndef PI
#define PI 3.14159265359
#endif

#ifndef EPS
#define EPS 1e-7
#endif

MixedDistribution::MixedDistribution(double p, MainDistribution component1, MainDistribution component2) :
	_p(p < 0 || p > 1 ? throw std::string("Value error: p must be clamp between 0 and 1") : p),
	_component1(component1),
	_component2(component2) {}

MixedDistribution::MixedDistribution(std::string file_name)
{
	load_from_file(file_name);
}

void MixedDistribution::set_p(double p)
{
	if (p < 0 || p > 1)
	{
		throw std::string("Value error: p must be clamp between 0 and 1");
	}

	_p = p;
}

double MixedDistribution::generate_value() const
{
	double r = static_cast<double>(rand()) / RAND_MAX;

	if (r > _p)
	{
		return _component1.generate_value();
	}

	else
	{
		return _component2.generate_value();
	}
}

double MixedDistribution::get_density(double x) const
{
	return (1 - _p) * _component1.get_density(x) + _p * _component2.get_density(x);
}

double MixedDistribution::get_expected_value() const
{
	return (1 - _p) * _component1.get_expected_value() + _p * _component2.get_expected_value();
}

double MixedDistribution::get_dispersion() const
{
	const double mix_expected_value = get_expected_value();
	const double expected_value1 = _component1.get_expected_value();
	const double expected_value2 = _component2.get_expected_value();
	const double dispersion1 = _component1.get_dispersion();
	const double dispersion2 = _component2.get_dispersion();

	return	(1 - _p) * (pow(expected_value1, 2) + dispersion1)
		+ _p * (pow(expected_value2, 2) + dispersion2)
		- pow(mix_expected_value, 2);
}

double MixedDistribution::get_skewness() const
{
	double mix_expected_value = get_expected_value();
	double mix_dispersion = get_dispersion();
	double expected_value1 = _component1.get_expected_value();
	double expected_value2 = _component2.get_expected_value();
	double dispersion1 = _component1.get_dispersion();
	double dispersion2 = _component2.get_dispersion();
	double skewness1 = _component1.get_skewness();
	double skewness2 = _component2.get_skewness();

	return	((1 - _p) * (pow(expected_value1 - mix_expected_value, 3) + 3 * (expected_value1 - mix_expected_value)
		* dispersion1 + pow(dispersion1, 1.5) * skewness1)
		+ _p * (pow(expected_value2 - mix_expected_value, 3) + 3 * (expected_value2 - mix_expected_value)
			* dispersion2 + pow(dispersion2, 1.5) * skewness2))
		/ pow(mix_dispersion, 1.5);
}

double MixedDistribution::get_kurtosis() const
{
	double mix_expected_value = get_expected_value();
	double mix_dispersion = get_dispersion();
	double expected_value1 = _component1.get_expected_value();
	double expected_value2 = _component2.get_expected_value();
	double dispersion1 = _component1.get_dispersion();
	double dispersion2 = _component2.get_dispersion();
	double skewness1 = _component1.get_skewness();
	double skewness2 = _component2.get_skewness();
	double kurtosis1 = _component1.get_kurtosis();
	double kurtosis2 = _component2.get_kurtosis();

	return	((1 - _p) * (pow(expected_value1 - mix_expected_value, 4) + 6 * pow(expected_value1 - mix_expected_value, 2)
		* dispersion1 + 4 * (expected_value1 - mix_expected_value) * pow(dispersion1, 1.5) * skewness1
		+ pow(dispersion1, 2) * (kurtosis1 + 3))
		+ _p * (pow(expected_value2 - mix_expected_value, 4) + 6 * pow(expected_value2 - mix_expected_value, 2)
			* dispersion2 + 4 * (expected_value2 - mix_expected_value) * pow(dispersion2, 1.5) * skewness2
			+ pow(dispersion2, 2) * (kurtosis2 + 3)))
		/ pow(mix_dispersion, 2) - 3;
}

void MixedDistribution::save_to_file(std::string file_name) const
{
	std::ofstream file(file_name);

	file << _p << '\n';
	file << _component1.get_v() << '\n';
	file << _component1.get_u() << '\n';
	file << _component1.get_l() << '\n';
	file << _component2.get_v() << '\n';
	file << _component2.get_u() << '\n';
	file << _component2.get_l();

	file.close();
}

void MixedDistribution::load_from_file(std::string file_name)
{
	std::ifstream file(file_name);
	if (!file)
	{
		throw std::string("Save file for MixedDistribution not found");
	}

	double p = 0, v1 = 0, u1 = 0, l1 = 1, v2 = 0, u2 = 0, l2 = 1;

	file >> p;
	file >> v1;
	file >> u1;
	file >> l1;
	file >> v2;
	file >> u2;
	file >> l2;

	if (!file)
	{
		file.close();
		throw std::string("Save file broken");
	}
	file.close();

	if (p < 0 || p > 1)
	{
		throw std::string("Value error: p must be clamp between 0 and 1");
	}

	_p = p;
	_component1.set_v(v1);
	_component1.set_u(u1);
	_component1.set_l(l1);
	_component2.set_v(v2);
	_component2.set_u(u2);
	_component2.set_l(l2);
}