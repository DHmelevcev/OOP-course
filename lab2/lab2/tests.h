#ifndef TESTS
#define TESTS

#include "main_distribution.h"
#include <iostream>
#include <iomanip>
#include "../../UI/scene.h"

constexpr int WINX = XCELLS * CELL_W + 40, WINY = YCELLS * CELL_H + 40;

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
}

#endif