#ifndef MAIN_DISTRIBUTION
#define MAIN_DISTRIBUTION

#include "spec_func.hpp"
#include "fstream"
#include "string"

class MainDistribution
{
public:
	MainDistribution(double v, double u, double l);
	MainDistribution(std::string file_name);

	inline double get_v() const { return _v; }
	inline double get_u() const { return _u; }
	inline double get_l() const { return _l; }
	
	void set_v(double v);
	void set_u(double u);
	void set_l(double l);

	double generate_value() const;

	double get_density(double x) const;

	double get_expected_value() const;

	double get_dispersion() const;

	double get_skewness() const;

	double get_kurtosis() const;

	void save_to_file(std::string file_name) const;

	void load_from_file(std::string file_name);

private:
	double _v, _u, _l;
};

#endif