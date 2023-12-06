#pragma once

#include "distribution.h"
#include "persistent.h"
#include "spec_func.hpp"
#include <fstream>

class MainDistribution : public IDistribution, public IPersistent
{
public:
	MainDistribution() noexcept;
	MainDistribution(const double v, const double u, const double l);
	MainDistribution(const std::string file_name);

	inline double get_v() const { return _v; }
	inline double get_u() const { return _u; }
	inline double get_l() const { return _l; }
	
	void set_v(const double v);
	void set_u(const double u);
	void set_l(const double l);

	double generate_value() const override;

	double get_density(const double x) const override;

	double get_expected_value() const override;

	double get_dispersion() const override;

	double get_skewness() const override;

	double get_kurtosis() const override;

	void save_to_file(const std::string file_name) const override;

	void load_from_file(const std::string file_name) override;

private:
	double _v, _u, _l;
};