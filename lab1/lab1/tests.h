#ifndef TESTS
#define TESTS

#include "main_distribution.h"
#include "mixture_distibution.h"
#include "empirical_distribution.h"
#include <iostream>
#include <iomanip>

namespace test
{
	void main_distribution_density();
	void main_distribution_transforms();

	void mix_distribution_density();
	void mix_distribution_expected_value();
	void mix_distribution_dispersion();

	void emp_distribution();
}

#endif