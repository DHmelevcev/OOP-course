#pragma once

#include "distribution.h"
#include "persistent.h"
#include <algorithm>
#include <fstream>

class EmpiricalDistribution : public IDistribution, public IPersistent
{
public:
	EmpiricalDistribution(const size_t n, const IDistribution& main_distr, size_t k = 1);
	EmpiricalDistribution(const std::string file_name);

	EmpiricalDistribution(const EmpiricalDistribution& empirical_distr)  noexcept;

	EmpiricalDistribution& operator=(const EmpiricalDistribution& empirical_distr);

	inline size_t get_n() const { return _n; }
	inline size_t get_k() const { return _k; }

	std::pair<std::pair<double, double>, double> get_interval(const size_t k) const;

	void set_k(const size_t k);

	double generate_value() const override;

	double get_density(const double x) const override;

	double get_expected_value() const override;

	double get_dispersion() const override;

	double get_skewness() const override;

	double get_kurtosis() const override;

	void save_to_file(const std::string file_name) const override;

	void load_from_file(const std::string file_name) override;

	~EmpiricalDistribution();

private:
	void calculate_distribution();

	size_t _n;
	double* _sample;
	size_t _k;
	double* _freq;
	double _start;
	double _delta;
};