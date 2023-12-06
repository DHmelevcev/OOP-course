#pragma once

#include "distribution.h"
#include "persistent.h"

template<class Distribution1, class Distribution2>
class MixedDistribution : public IDistribution, public IPersistent
{
public:
	MixedDistribution(const double p, const Distribution1& component1, const Distribution2& component2) :
		_p(p < 0 || p > 1 ? throw std::string("Value error: p must be clamp between 0 and 1") : p),
		_component1(component1),
		_component2(component2) {}

	MixedDistribution(const std::string file_name)
	{
		load_from_file(file_name);
	}

	inline Distribution1& component1() { return _component1; }
	inline Distribution2& component2() { return _component2; }
	inline double get_p() const { return _p; }

	void set_p(const double p)
	{
		if (p < 0 || p > 1)
		{
			throw std::string("Value error: p must be clamp between 0 and 1");
		}

		_p = p;
	}

	double generate_value() const override
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

	double get_density(const double x) const override
	{
		return (1 - _p) * _component1.get_density(x) + _p * _component2.get_density(x);
	}

	double get_expected_value() const override
	{
		return (1 - _p) * _component1.get_expected_value() + _p * _component2.get_expected_value();
	}

	double get_dispersion() const override
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

	double get_skewness() const override
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

	double get_kurtosis() const override
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

	void save_to_file(const std::string file_name) const override
	{
		std::ofstream file(file_name + ".distrm");
		file << _p;
		file.close();

		_component1.save_to_file(file_name + "_1");
		_component2.save_to_file(file_name + "_2");
	}

	void load_from_file(const std::string file_name) override
	{
		std::ifstream file(file_name + ".distrm");
		double p;
		file >> p;
		file.close();
		if (p < 0 || p > 1)
		{
			throw std::string("Value error: p must be clamp between 0 and 1");
		}
		_p = p;

		_component1.load_from_file(file_name + "_1");
		_component2.load_from_file(file_name + "_2");
	}

private:
	double _p;
	Distribution1 _component1;
	Distribution2 _component2;
};