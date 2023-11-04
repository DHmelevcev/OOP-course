#ifndef EMPIRICAL_DISTRIBUTION
#define EMPIRICAL_DISTRIBUTION

#include "main_distribution.h"
#include "mixed_distribution.h"
#include "map"
#include "algorithm"

class EmpiricalDistribution
{
public:
	EmpiricalDistribution(size_t n, const MainDistribution& main_distr, size_t k = 1);
	EmpiricalDistribution(size_t n, const MixedDistribution& mixed_distr, size_t k = 1);
	EmpiricalDistribution(size_t n, const EmpiricalDistribution& empirical_distr, size_t k = 1);

	EmpiricalDistribution(const EmpiricalDistribution& empirical_distr)  noexcept;

	EmpiricalDistribution& operator=(const EmpiricalDistribution& empirical_distr);

	inline size_t get_n() const { return _n; }
	inline size_t get_k() const { return _freq.size(); }

	std::pair<std::pair<double, double>, double> get_interval(size_t k) const;

	void set_k(size_t k);

	double generate_value() const;

	double get_density(double x) const;

	double get_expected_value();

	double get_dispersion();

	double get_skewness();

	double get_kurtosis();

	void save_to_file(std::string file_name) const;

	void load_from_file(std::string file_name);

	~EmpiricalDistribution();

private:
	void calculate_distribution(size_t k);

	size_t _n;
	double* _sample;
	std::map<std::pair<double, double>, double> _freq;
};

#endif