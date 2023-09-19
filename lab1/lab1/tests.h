#ifndef TESTS
#define TESTS

#include "main_distribution.h"
#include "mixture_distibution.h"
#include "empirical_distribution.h"
#include <iostream>
#include <iomanip>

namespace test
{
	bool main_distribution_density();
	bool main_distribution_transforms();

	bool mix_distribution_density();
	bool mix_distribution_expected_value();
	bool mix_distribution_dispersion();

	void emp_distribution();
}

#endif