#include "tests.h"

#ifndef EPS
#define EPS 1e-3
#endif

namespace test
{
	bool main_distribution_density()
	{
		std::cout << "Main distribution density test:\n";
		bool result = true;

		std::vector<double> v = { 0., 0.5, 1., 2., 3., 4., 5., 6., 7., 8. };
		double u = 0;
		double l = 1;
		std::vector<double> f = { 0.5, 0.637, 0.75, 0.938, 1.094, 1.23, 1.354, 1.466, 1.571, 1.669 };
		double x = 0;

		for (std::vector<double>::const_iterator itv = v.begin(), itf = f.begin(); itv != v.end() && itf != f.end(); itv++, itf++)
		{
			MainDistribution distr(*itv, u, l);
			double density = distr.get_density(x);
			std::cout << density << ' ' << *itf << "\n";

			if (abs(density - *itf) > EPS)
			{
				result = false;
			}
		}

		std::cout << "Result: " << (result? "correct" : "error") << "\n\n";
		return result;
	}

	bool main_distribution_transforms()
	{
		std::cout << "Main distribution transforms test:\n";
		bool result = true;

		double v = 0.5;
		double u = 0.7;
		double l = 2;
		double x = 0;

		double f = 0.29818;

		MainDistribution distr(v, u, l);
		double density = distr.get_density(x);
		std::cout << density << ' ' << f << "\n";

		if (abs(density - f) > EPS)
		{
			result = false;
		}

		std::cout << "Result: " << (result ? "correct" : "error") << "\n\n";
		return result;
	}

	bool main_distribution_expected_value()
	{
		std::cout << "Main distribution expected value test:\n";
		bool result = true;

		double v = 0.5;
		double u = 0.7;
		double l = 1;

		double f = 0.7;

		MainDistribution distr(v, u, l);
		double expected_value = distr.get_expected_value();
		std::cout << expected_value << ' ' << f << "\n";

		if (abs(expected_value - f) > EPS)
		{
			result = false;
		}

		std::cout << "Result: " << (result ? "correct" : "error") << "\n\n";
		return result;
	}

	bool main_distribution_dispersion()
	{
		std::cout << "Main distribution expected value test:\n";
		bool result = true;

		double v = 0.4;
		double u = 0.7;
		double l = 1.2;

		double f = 0.37895;

		MainDistribution distr(v, u, l);
		double dispersion = distr.get_dispersion();
		std::cout << dispersion << ' ' << f << "\n";

		if (abs(dispersion - f) > EPS)
		{
			result = false;
		}

		std::cout << "Result: " << (result ? "correct" : "error") << "\n\n";
		return result;
	}

	bool main_distribution_skewness()
	{
		std::cout << "Main distribution skewness test:\n";
		bool result = true;

		double v = 0.3;
		double u = 1;
		double l = 1.5;

		double f = 0.;

		MainDistribution distr(v, u, l);
		double skewness = distr.get_skewness();
		std::cout << skewness << ' ' << f << "\n";

		if (abs(skewness - f) > EPS)
		{
			result = false;
		}

		std::cout << "Result: " << (result ? "correct" : "error") << "\n\n";
		return result;
	}

	bool main_distribution_kurtosis()
	{
		std::cout << "Main distribution kurtosis test:\n";
		bool result = true;

		double v = 0.5;
		double u = 1;
		double l = 2;

		double f = -1.;

		MainDistribution distr(v, u, l);
		double kurtosis = distr.get_kurtosis();
		std::cout << kurtosis << ' ' << f << "\n";

		if (abs(kurtosis - f) > EPS)
		{
			result = false;
		}

		std::cout << "Result: " << (result ? "correct" : "error") << "\n\n";
		return result;
	}

	bool main_distribution_save()
	{
		std::cout << "Main distribution save test:\n";
		bool result = true;

		double v = 0.5;
		double u = 1;
		double l = 2;

		MainDistribution distr(v, u, l);
		distr.save_to_file("temp.distr");

		std::ifstream file("temp.distr");
		double rv, ru, rl;
		file >> rv;
		file >> ru;
		file >> rl;

		file.close();
		remove("temp.distr");

		if (v != rv || u != ru || l != rl)
		{
			result = false;
		}

		std::cout << "Result: " << (result ? "correct" : "error") << "\n\n";
		return result;
	}

	bool main_distribution_load()
	{
		std::cout << "Main distribution load test:\n";
		bool result = true;

		double v = 0.5;
		double u = 1;
		double l = 2;


		std::ofstream file("temp.distr");
		file << v << '\n';
		file << u << '\n';
		file << l;

		file.close();

		MainDistribution distr1("temp.distr");
		MainDistribution distr2(1, 2, 3);
		distr2.load_from_file("temp.distr");
		remove("temp.distr");

		if (distr1.get_v() != v || distr1.get_u() != u || distr1.get_l() != l || distr2.get_v() != v || distr2.get_u() != u || distr2.get_l() != l)
		{
			result = false;
		}

		std::cout << "Result: " << (result ? "correct" : "error") << "\n\n";
		return result;
	}

	bool mixed_distribution_density()
	{
		std::cout << "Mixed distribution density test:\n";
		bool result = true;

		double v1 = 0.5;
		double v2 = 0.5;
		double u1 = 1;
		double u2 = 1;
		double l1 = 2;
		double l2 = 2;
		double p = 0.5;
		double x = 0;

		double fmix = 0.275664;

		MixedDistribution distr(p, MainDistribution(v1, u1, l1), MainDistribution(v2, u2, l2));
		double density = distr.get_density(x);
		std::cout << density << ' ' << fmix << "\n";

		if (abs(density - fmix) > EPS)
		{
			result = false;
		}

		std::cout << "Result: " << (result ? "correct" : "error") << "\n\n";
		return result;
	}

	bool mixed_distribution_expected_value()
	{
		std::cout << "Mixed distribution transforms test:\n";
		bool result = true;

		double v1 = 5;
		double v2 = 15;
		double u1 = 2;
		double u2 = 4;
		double l1 = 3;
		double l2 = 1;
		double p = 0.5;

		double f = 3;

		MixedDistribution distr(p, MainDistribution(v1, u1, l1), MainDistribution(v2, u2, l2));
		double expected_value = distr.get_expected_value();
		std::cout << expected_value << ' ' << f << "\n";

		if (abs(expected_value - f) > EPS)
		{
			result = false;
		}

		std::cout << "Result: " << (result ? "correct" : "error") << "\n\n";
		return result;
	}

	bool mixed_distribution_dispersion()
	{
		std::cout << "Mixed distribution expected value test:\n";
		bool result = true;

		double v1 = 1;
		double v2 = 1;
		double u1 = 0;
		double u2 = 0;
		double l1 = 1;
		double l2 = 3;
		double p = 0.5;

		double f = 1;

		MixedDistribution distr(p, MainDistribution(v1, u1, l1), MainDistribution(v2, u2, l2));
		double dispersion = distr.get_dispersion();
		std::cout << dispersion << ' ' << f << "\n";

		if (abs(dispersion - f) > EPS)
		{
			result = false;
		}

		std::cout << "Result: " << (result ? "correct" : "error") << "\n\n";
		return result;
	}

	bool mixed_distribution_save()
	{
		std::cout << "Mixed distribution save test:\n";
		bool result = true;

		double p = 0.5;
		double v1 = 1;
		double v2 = 1;
		double u1 = 0;
		double u2 = 0;
		double l1 = 1;
		double l2 = 3;

		MixedDistribution distr(p, MainDistribution(v1, u1, l1), MainDistribution(v2, u2, l2));
		distr.save_to_file("temp.distr");

		std::ifstream file("temp.distr");
		double rp, rv1, ru1, rl1, rv2, ru2, rl2;
		file >> rp;
		file >> rv1;
		file >> ru1;
		file >> rl1;
		file >> rv2;
		file >> ru2;
		file >> rl2;

		file.close();
		remove("temp.distr");

		if (p != rp || v1 != rv1 || u1 != ru1 || l1 != rl1 || v2 != rv2 || u2 != ru2 || l2 != rl2)
		{
			result = false;
		}

		std::cout << "Result: " << (result ? "correct" : "error") << "\n\n";
		return result;
	}

	bool mixed_distribution_load()
	{
		std::cout << "Mixed distribution load test:\n";
		bool result = true;

		double p = 0.5;
		double v1 = 1;
		double v2 = 1;
		double u1 = 0;
		double u2 = 0;
		double l1 = 1;
		double l2 = 3;

		std::ofstream file("temp.distr");
		file << p << '\n';
		file << v1 << '\n';
		file << u1 << '\n';
		file << l1 << '\n';
		file << v2 << '\n';
		file << u2 << '\n';
		file << l2;

		file.close();

		MixedDistribution distr1("temp.distr");
		MixedDistribution distr2(p, MainDistribution(v1, u1, l1), MainDistribution(v2, u2, l2));
		distr2.load_from_file("temp.distr");
		remove("temp.distr");

		if (distr1.component1().get_v() != v1 || distr1.component1().get_u() != u1 || distr1.component1().get_l() != l1 ||
			distr2.component1().get_v() != v1 || distr2.component1().get_u() != u1 || distr2.component1().get_l() != l1 ||
			distr1.component2().get_v() != v2 || distr1.component2().get_u() != u2 || distr1.component2().get_l() != l2 ||
			distr2.component2().get_v() != v2 || distr2.component2().get_u() != u2 || distr2.component2().get_l() != l2)
		{
			result = false;
		}

		std::cout << "Result: " << (result ? "correct" : "error") << "\n\n";
		return result;
	}
}