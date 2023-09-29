#include "tests.h"

#ifndef EPS
#define EPS 1e-3
#endif

namespace test
{
	void main_distribution_density()
	{
		std::vector<double> v = { 0, 0.5, 1, 2, 3, 4, 5, 6, 7, 8 };
		double u = 0;
		double l = 1;
		std::vector<double> f = { 0.5, 0.637, 0.75, 0.938, 1.094, 1.23, 1.354, 1.466, 1.571, 1.669 };
		double x = 0;
		
		for (std::vector<double>::const_iterator itv = v.begin(), itf = f.begin(); itv != v.end() && itf != f.end(); itv++, itf++)
		{
			if (abs(distr::get_density(x, *itv, u, l) - *itf) > EPS)
			{
				std::cout << "Main distribution density: ERROR\n";
				return;
			}
		}

		std::cout << "Main distribution density: correct\n";
		return;
	}

	void main_distribution_transforms()
	{
		double v = 0.5;
		double u = 0.7;
		double l = 2;
		double x = 0;

		double f = 0.298177;

		if (abs(distr::get_density(x, v, u, l) - f) > EPS)
		{
			std::cout << " " << "Main distribution transforms: ERROR\n";
			return;
		}

		std::cout << "Main distribution transforms: correct\n";
		return;
	}
	
	void mix_distribution_density()
	{
		double v1 = 0.5;
		double v2 = 0.5;
		double u1 = 1;
		double u2 = 1;
		double l1 = 2;
		double l2 = 2;
		double p = 0.5;
		double x = 0;

		double fmix = 0.275664;

		if (abs(distrmix::get_density(x, v1, u1, l1, v2, u2, l2, p) - fmix) > EPS)
		{
			std::cout << "Mixed distribution density: ERROR\n";
			return;
		}

		std::cout << "Mixed distribution density: correct\n";
		return;
	}

	void mix_distribution_expected_value()
	{
		double v1 = 5;
		double v2 = 15;
		double u1 = 2;
		double u2 = 4;
		double l1 = 3;
		double l2 = 1;
		double p = 0.5;

		double expected_value = 3;

		if (abs(distrmix::get_expected_value(v1, u1, l1, v2, u2, l2, p) - expected_value) > EPS)
		{
			std::cout << "Mixed distribution expected value: ERROR\n";
			return;
		}

		std::cout << "Mixed distribution expected value: correct\n";
		return;
	}

	void mix_distribution_dispersion()
	{
		double v1 = 1;
		double v2 = 1;
		double u1 = 0;
		double u2 = 0;
		double l1 = 1;
		double l2 = 3;
		double p = 0.5;

		double dispersion = 1;

		if (abs(distrmix::get_dispersion(v1, u1, l1, v2, u2, l2, p) - dispersion) > EPS)
		{
			std::cout << "Mixed distribution dispersion: ERROR\n";
			return;
		}

		std::cout << "Mixed distribution dispersion: correct\n";
		return;
	}

	void emp_distribution(int testNum, MyScene& scene)
	{
		std::cout << "====================================================\nEmpirical distribution test";

		if (testNum >=1 && testNum <=3)
		{
			std::cout << " (Main)\n\n";

			size_t n = testNum == 1 ? 100 : testNum == 2 ? 10000 : 1000000;

			double v = 0.5;
			double u = 10;
			double l = 2;

			std::vector<double> x = { 4, 4.5, 5.1, 5.5, 6, 6.5, 6.9, 7.5, 8.1, 8.5, 9, 9.5, 10, 10.5, 11, 11.5, 11.9, 12.5, 13 };

			std::cout << "Theoretical expected value: " << distr::get_expected_value(v, u, l) << "\n";
			std::cout << "Theoretical dispersion:     " << distr::get_dispersion(v, u, l) << "\n";
			std::cout << "Theoretical skewness:       " << distr::get_skewness(v, u, l) << "\n";
			std::cout << "Theoretical kurtosis:       " << distr::get_kurtosis(v, u, l) << "\n\n";

			std::vector<double> sample;
			sample.resize(n);
			for (size_t i = 0; i < n; i++)
			{
				sample[i] = distr::generate_value(v, u, l);
			}
			std::map<std::pair<double, double>, double> emp_distr = distremp::create_distribution(sample);

			std::cout << "N = " << n << "\n";
			std::cout << "Empirical expected value:   " << distremp::get_expected_value(sample) << "\n";
			std::cout << "Empirical dispersion:       " << distremp::get_dispersion(sample) << "\n";
			std::cout << "Empirical skewness:         " << distremp::get_skewness(sample) << "\n";
			std::cout << "Empirical kurtosis:         " << distremp::get_kurtosis(sample) << "\n\n";

			std::cout << "Density:     Theoretical"
				<< "  N =" << std::setw(8) << n << "\n";
			for (std::vector<double>::const_iterator it = x.begin(); it != x.end(); it++)
			{
				std::cout << "x =" << std::setw(8) << *it
					<< std::setw(13) << distr::get_density(*it, v, u, l)
					<< std::setw(13) << distremp::get_density(emp_distr, *it) << "\n";
			}

			LineStrip lineStrip(WINX + 1);
			for (int i = 0; i <= WINX; i++)
			{
				lineStrip.X[i] = static_cast<double>(i) * 3 * l / WINX + u - 1.5 * l;
				lineStrip.Y[i] = distr::get_density(lineStrip.X[i], v, u, l);
			}
			scene.set_plot(lineStrip, 3 * l / XCELLS, 0.01, u - 1.5 * l);

			size_t dots_size = sample.size() > 1e3 ? 1e3 : sample.size();
			Dots dots(dots_size);
			for (int i = 0; i < dots_size; i++)
			{
				dots.X[i] = sample[i];
				dots.Y[i] = distr::get_density(dots.X[i], v, u, l);
			}
			scene.set_dots(dots, 3 * l / XCELLS, 0.01, u - 1.5 * l);

			Intervals intervals(emp_distr.size());
			int i = 0;
			for (std::map<std::pair<double, double>, double>::const_iterator it = emp_distr.begin(); it != emp_distr.end(); it++, i++)
			{
				intervals.Xinterval[i].first = it->first.first;
				intervals.Xinterval[i].second = it->first.second;
				intervals.Y[i] = it->second;
			}
			scene.set_plot(intervals, 3 * l / XCELLS, 0.01, u - 1.5 * l);

			Intervals intervals2(0);
			scene.set_plot_transparent(intervals2);
		}

		if (testNum >= 4 && testNum <= 6)
		{
			std::cout << " (Mixed)\n\n";

			size_t n = testNum == 4 ? 100 : testNum == 5 ? 10000 : 1000000;

			double v1 = 0.5;
			double u1 = 10;
			double l1 = 2;

			double v2 = 1;
			double u2 = 6;
			double l2 = 1;
			double p = 0.4;

			std::vector<double> x = { 4, 4.5, 5.1, 5.5, 6, 6.5, 6.9, 7.5, 8.1, 8.5, 9, 9.5, 10, 10.5, 11, 11.5, 11.9, 12.5, 13 };

			std::cout << "Theoretical expected value: " << distrmix::get_expected_value(v1, u1, l1, v2, u2, l2, p) << "\n";
			std::cout << "Theoretical dispersion:     " << distrmix::get_dispersion(v1, u1, l1, v2, u2, l2, p) << "\n";
			std::cout << "Theoretical skewness:       " << distrmix::get_skewness(v1, u1, l1, v2, u2, l2, p) << "\n";
			std::cout << "Theoretical kurtosis:       " << distrmix::get_kurtosis(v1, u1, l1, v2, u2, l2, p) << "\n\n";

			std::vector<double> sample;
			sample.resize(n);
			for (size_t i = 0; i < n; i++)
			{
				sample[i] = distrmix::generate_value(v1, u1, l1, v2, u2, l2, p);
			}
			std::map<std::pair<double, double>, double> emp_distr = distremp::create_distribution(sample);

			std::cout << "N = " << n << "\n";
			std::cout << "Empirical expected value:   " << distremp::get_expected_value(sample) << "\n";
			std::cout << "Empirical dispersion:       " << distremp::get_dispersion(sample) << "\n";
			std::cout << "Empirical skewness:         " << distremp::get_skewness(sample) << "\n";
			std::cout << "Empirical kurtosis:         " << distremp::get_kurtosis(sample) << "\n\n";

			std::cout << "Density:     Theoretical"
				<< "  N =" << std::setw(8) << n << "\n";
			for (std::vector<double>::const_iterator it = x.begin(); it != x.end(); it++)
			{
				std::cout << "x =" << std::setw(8) << *it
					<< std::setw(13) << distrmix::get_density(*it, v1, u1, l1, v2, u2, l2, p)
					<< std::setw(13) << distremp::get_density(emp_distr, *it) << "\n";
			}

			LineStrip lineSrtip(WINX + 1);
			for (int i = 0; i <= WINX; i++)
			{
				lineSrtip.X[i] = static_cast<double>(i) * (*x.rbegin() - *x.begin()) / WINX + *x.begin();
				lineSrtip.Y[i] = distrmix::get_density(lineSrtip.X[i], v1, u1, l1, v2, u2, l2, p);
			}
			scene.set_plot(lineSrtip, (*x.rbegin() - *x.begin()) / XCELLS, 0.01, *x.begin());

			size_t dots_size = sample.size() > 1e3 ? 1e3 : sample.size();
			Dots dots(dots_size);
			for (int i = 0; i < dots_size; i++)
			{
				dots.X[i] = sample[i];
				dots.Y[i] = distrmix::get_density(dots.X[i], v1, u1, l1, v2, u2, l2, p);
			}
			scene.set_dots(dots, (*x.rbegin() - *x.begin()) / XCELLS, 0.01, *x.begin());

			Intervals intervals(emp_distr.size());
			int i = 0;
			for (std::map<std::pair<double, double>, double>::const_iterator it = emp_distr.begin(); it != emp_distr.end(); it++, i++)
			{
				intervals.Xinterval[i].first = it->first.first;
				intervals.Xinterval[i].second = it->first.second;
				intervals.Y[i] = it->second;
			}
			scene.set_plot(intervals, (*x.rbegin() - *x.begin()) / XCELLS, 0.01, *x.begin());

			Intervals intervals2(0);
			scene.set_plot_transparent(intervals2);
		}

		if (testNum == 7)
		{
			std::cout << " (Empirical)\n\n";

			size_t n = 1000000;

			double v = 1;
			double u = 10;
			double l = 2;

			std::vector<double> sample;
			sample.resize(n);
			for (size_t i = 0; i < n; i++)
			{
				sample[i] = distr::generate_value(v, u, l);
			}
			std::map<std::pair<double, double>, double> emp_distr = distremp::create_distribution(sample);

			std::cout << "Theoretical expected value:           " << distr::get_expected_value(v, u, l) << "\n";
			std::cout << "Theoretical dispersion:               " << distr::get_dispersion(v, u, l) << "\n";
			std::cout << "Theoretical skewness:                 " << distr::get_skewness(v, u, l) << "\n";
			std::cout << "Theoretical kurtosis:                 " << distr::get_kurtosis(v, u, l) << "\n\n";

			std::cout << "N = " << n << "\n";
			std::cout << "Empirical 1st stage expected value:   " << distremp::get_expected_value(sample) << "\n";
			std::cout << "Empirical 1st stage dispersion:       " << distremp::get_dispersion(sample) << "\n";
			std::cout << "Empirical 1st stage skewness:         " << distremp::get_skewness(sample) << "\n";
			std::cout << "Empirical 1st stage kurtosis:         " << distremp::get_kurtosis(sample) << "\n\n";

			std::vector<double> sample2;
			sample2.resize(n);
			for (size_t i = 0; i < n; i++)
			{
				double p = static_cast<double>(rand()) / RAND_MAX;

				auto it = emp_distr.begin();
				do {
					p -= it->second * (it->first.second - it->first.first); it++;
				} while (p > 1e-7);
				it--;

				sample2[i] = static_cast<double>(rand()) / RAND_MAX * (it->first.second - it->first.first) + it->first.first;
			}
			std::map<std::pair<double, double>, double> emp_distr2 = distremp::create_distribution(sample2);

			std::cout << "Empirical 2nd stage expected value:   " << distremp::get_expected_value(sample2) << "\n";
			std::cout << "Empirical 2nd stage dispersion:       " << distremp::get_dispersion(sample2) << "\n";
			std::cout << "Empirical 2nd stage skewness:         " << distremp::get_skewness(sample2) << "\n";
			std::cout << "Empirical 2nd stage kurtosis:         " << distremp::get_kurtosis(sample2) << "\n\n";

			std::cout << "Density:     Theoretical  Empirical 1st stage  Empirical 2nd stage\n";
			for (auto it = emp_distr.begin(); it != emp_distr.end(); it++)
			{
				double x = (it->first.second + it->first.first) / 2;
				std::cout << "x =" << std::setw(8) << x
					<< std::setw(13) << distr::get_density(x, v, u, l)
					<< std::setw(21) << distremp::get_density(emp_distr, x)
					<< std::setw(21) << distremp::get_density(emp_distr2, x) << "\n";
			}

			LineStrip lineStrip(WINX + 1);
			for (int i = 0; i <= WINX; i++)
			{
				lineStrip.X[i] = static_cast<double>(i) * 3 * l / WINX + u - 1.5 * l;
				lineStrip.Y[i] = distr::get_density(lineStrip.X[i], v, u, l);
			}
			scene.set_plot(lineStrip, 3 * l / XCELLS, 0.01, u - 1.5 * l);

			Intervals intervals(emp_distr.size());
			int i = 0;
			for (std::map<std::pair<double, double>, double>::const_iterator it = emp_distr.begin(); it != emp_distr.end(); it++, i++)
			{
				intervals.Xinterval[i].first = it->first.first;
				intervals.Xinterval[i].second = it->first.second;
				intervals.Y[i] = it->second;
			}
			scene.set_plot(intervals, 3 * l / XCELLS, 0.01, u - 1.5 * l);

			size_t dots_size = sample.size() > 1e3 ? 1e3 : sample.size();
			Dots dots(dots_size);
			for (int i = 0; i < dots_size; i++)
			{
				dots.X[i] = sample[i];
				dots.Y[i] = distr::get_density(dots.X[i], v, u, l);
			}
			scene.set_dots(dots, 3 * l / XCELLS, 0.01, u - 1.5 * l);


			Intervals intervals2(emp_distr2.size());
			i = 0;
			for (std::map<std::pair<double, double>, double>::const_iterator it = emp_distr2.begin(); it != emp_distr2.end(); it++, i++)
			{
				intervals2.Xinterval[i].first = it->first.first;
				intervals2.Xinterval[i].second = it->first.second;
				intervals2.Y[i] = it->second;
			}
			scene.set_plot_transparent(intervals2, 3 * l / XCELLS, 0.01, u - 1.5 * l);
		}

		return;
	}
}