#include "main_distribution.h"
#include "mixture_distibution.h"
#include "empirical_distribution.h"
#include "tests.h"
#include <iostream>

int main()
{
	srand(time(0));

	test::main_distribution_density();
	test::main_distribution_transforms();
	test::mix_distribution_density();
	test::mix_distribution_expected_value();
	test::mix_distribution_dispersion();
	test::emp_distribution();

	return 0;
}