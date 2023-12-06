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
		distr.save_to_file("temp");

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

		MainDistribution distr1("temp");
		MainDistribution distr2(1, 2, 3);
		distr2.load_from_file("temp");
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
		MainDistribution distr1(v1, u1, l1);
		MainDistribution distr2(v2, u2, l2);

		double fmix = 0.275664;

		MixedDistribution<MainDistribution, MainDistribution> distr(p, distr1, distr2);
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
		MainDistribution distr1(v1, u1, l1);
		MainDistribution distr2(v2, u2, l2);

		double f = 3;

		MixedDistribution<MainDistribution, MainDistribution> distr(p, distr1, distr2);
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
		MainDistribution distr1(v1, u1, l1);
		MainDistribution distr2(v2, u2, l2);

		double f = 1;

		MixedDistribution<MainDistribution, MainDistribution> distr(p, distr1, distr2);
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
		MainDistribution distr1(v1, u1, l1);
		MainDistribution distr2(v2, u2, l2);

		MixedDistribution<MainDistribution, MainDistribution> distr(p, distr1, distr2);
		distr.save_to_file("temp");

		double rp, rv1, ru1, rl1, rv2, ru2, rl2;
		std::ifstream file0("temp.distrm");
		file0 >> rp;
		std::ifstream file01("temp_1.distr");
		file01 >> rv1;
		file01 >> ru1;
		file01 >> rl1;
		std::ifstream file02("temp_2.distr");
		file02 >> rv2;
		file02 >> ru2;
		file02 >> rl2;

		file0.close();
		file01.close();
		file02.close();
		remove("temp.distrm");
		remove("temp_1.distr");
		remove("temp_2.distr");

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

		std::ofstream file0("temp.distrm");
		file0 << p << '\n';
		std::ofstream file1("temp_1.distr");
		file1 << v1 << '\n';
		file1 << u1 << '\n';
		file1 << l1 << '\n';
		std::ofstream file2("temp_2.distr");
		file2 << v2 << '\n';
		file2 << u2 << '\n';
		file2 << l2;
		MainDistribution distr01(v1, u1, l1);
		MainDistribution distr02(v2, u2, l2);

		file0.close();
		file1.close();
		file2.close();

		MixedDistribution<MainDistribution, MainDistribution> distr1("temp");
		MixedDistribution<MainDistribution, MainDistribution> distr2(p, distr01, distr02);
		MixedDistribution<MainDistribution, MainDistribution> distr3(p, distr01, distr02);
		distr3.load_from_file("temp");
		remove("temp.distrm");
		remove("temp_1.distr");
		remove("temp_2.distr");

		if (distr1.component1().get_v() != v1 || distr1.component1().get_u() != u1 || distr1.component1().get_l() != l1 ||
			distr2.component1().get_v() != v1 || distr2.component1().get_u() != u1 || distr2.component1().get_l() != l1 ||
			distr3.component1().get_v() != v1 || distr3.component1().get_u() != u1 || distr3.component1().get_l() != l1 ||
			distr1.component2().get_v() != v2 || distr1.component2().get_u() != u2 || distr1.component2().get_l() != l2 ||
			distr2.component2().get_v() != v2 || distr2.component2().get_u() != u2 || distr2.component2().get_l() != l2 ||
			distr3.component2().get_v() != v2 || distr3.component2().get_u() != u2 || distr3.component2().get_l() != l2)
		{
			result = false;
		}

		std::cout << "Result: " << (result ? "correct" : "error") << "\n\n";
		return result;
	}

	bool late_binding()
	{
		std::cout << "Late binding test:\n";
		bool result = true;

		double p = 0.5;
		double v1 = 1;
		double v2 = 1;
		double u1 = 0;
		double u2 = 0;
		double l1 = 1;
		double l2 = 3;

		try
		{
			std::vector<IDistribution*> distrs;

			// 0
			MainDistribution distr0(v1, u1, l1);
			distrs.emplace_back(&distr0);

			// 1
			MainDistribution distr1(v2, u2, l2);
			distrs.emplace_back(&distr1);

			// 2
			MixedDistribution<MainDistribution, MainDistribution> distr2(p,
				dynamic_cast<MainDistribution&>(*distrs[0]),
				dynamic_cast<MainDistribution&>(*distrs[1])
			);
			distrs.emplace_back(&distr2);

			// 3
			MixedDistribution<MainDistribution, MixedDistribution<MainDistribution, MainDistribution>> distr3(p,
				dynamic_cast<MainDistribution&>(*distrs[1]),
				dynamic_cast<MixedDistribution<MainDistribution, MainDistribution>&>(*distrs[2])
			);
			distrs.emplace_back(&distr3);

			// 4
			EmpiricalDistribution distr4(1000, *distrs[1]);
			distrs.emplace_back(&distr4);

			// 5
			EmpiricalDistribution distr5(1000, *distrs[3]);
			distrs.emplace_back(&distr5);

			// 6
			EmpiricalDistribution distr6(1000, *distrs[5]);
			distrs.emplace_back(&distr6);

			for (size_t i = 0; i < distrs.size(); ++i)
			{
				dynamic_cast<IPersistent&>(*distrs[i]).save_to_file("test" + std::to_string(i + 1));
			}
		}
		catch (std::string err)
		{
			std::cout << err;
			result = false;
		}

		std::cout << "Result: " << (result ? "correct" : "error") << "\n\n";
		return result;
	}
}