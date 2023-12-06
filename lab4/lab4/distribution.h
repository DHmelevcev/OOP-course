#pragma once

__interface IDistribution
{
	double generate_value() const;

	double get_density(double x) const;

	double get_expected_value() const;

	double get_dispersion() const;

	double get_skewness() const;

	double get_kurtosis() const;
};