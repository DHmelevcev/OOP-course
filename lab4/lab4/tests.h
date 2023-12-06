#pragma once

#include "main_distribution.h"
#include "mixed_distribution.h"
#include "empirical_distribution.h"
#include <iostream>
#include <vector>
#include <iomanip>

namespace test
{
	bool main_distribution_density();
	bool main_distribution_transforms();
	bool main_distribution_expected_value();
	bool main_distribution_dispersion();
	bool main_distribution_skewness();
	bool main_distribution_kurtosis();
	bool main_distribution_save();
	bool main_distribution_load();
	bool mixed_distribution_density();
	bool mixed_distribution_expected_value();
	bool mixed_distribution_dispersion();
	bool mixed_distribution_save();
	bool mixed_distribution_load();
	bool late_binding();
}