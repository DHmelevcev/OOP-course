#ifndef MIXED_DISTRIBUTION
#define MIXED_DISTRIBUTION

#include "main_distribution.h"

class MixedDistribution
{
public:
	MixedDistribution(double p, MainDistribution component1, MainDistribution component2);
	MixedDistribution(std::string file_name);

	inline MainDistribution& component1() { return _component1; }
	inline MainDistribution& component2() { return _component2; }
	inline double get_p() const { return _p; }

	void set_p(double p);

	double generate_value() const;

	double get_density(double x) const;

	double get_expected_value() const;

	double get_dispersion() const;

	double get_skewness() const;

	double get_kurtosis() const;

	void save_to_file(std::string file_name) const;

	void load_from_file(std::string file_name);

private:
	double _p;
	MainDistribution _component1;
	MainDistribution _component2;
};

#endif