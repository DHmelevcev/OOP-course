#ifndef TESTS
#define TESTS

#include "main_distribution.h"
#include "mixture_distibution.h"
#include "empirical_distribution.h"
#include <iostream>
#include <iomanip>
#include "../../UI/scene.h"

constexpr int WINX = XCELLS * CELL_W + 40, WINY = YCELLS * CELL_H + 40;

namespace test
{
	void main_distribution_density();
	void main_distribution_transforms();

	void mix_distribution_density();
	void mix_distribution_expected_value();
	void mix_distribution_dispersion();

	void emp_distribution(int testNum, MyScene& scene);
}

#endif