#include "main_distribution.h"
#include "mixed_distribution.h"
#include "empirical_distribution.h"
#include "tests.h"
#include "../../UI/scene.h"
#include <iostream>
#include <time.h>

constexpr int WINX = XCELLS * CELL_W + 40, WINY = YCELLS * CELL_H + 40;

#ifndef EPS
#define EPS 0.5e-1
#endif

#ifndef MAXINTERVALS
#define MAXINTERVALS 100
#endif

int main()
{
	srand(static_cast<uint32_t>(time(0)));

	try
	{
		test::main_distribution_density();
		test::main_distribution_transforms();
		test::main_distribution_expected_value();
		test::main_distribution_dispersion();
		test::main_distribution_skewness();
		test::main_distribution_kurtosis();
		test::main_distribution_save();
		test::main_distribution_load();
		test::mixed_distribution_density();
		test::mixed_distribution_expected_value();
		test::mixed_distribution_dispersion();
		test::mixed_distribution_save();
		test::mixed_distribution_load();
	}
	catch (std::string err)
	{
		std::cout << err << std::endl;
	}

	try
	{
		//initialisation
		const double p = 0.5, v1 = 1, u1 = 1.25, l1 = 1, v2 = 0.1, u2 = 3.75, l2 = 1;
		const size_t n = 10, k = 5;
		MainDistribution main_distr1(v1, u1, l1);
		MainDistribution main_distr2(v2, u2, l2);
		MixedDistribution mixed_distr(p, main_distr1, main_distr2);
		EmpiricalDistribution empirical_distr(n, main_distr1, k);

		sf::ContextSettings settings;
		settings.antialiasingLevel = 4;
		sf::RenderWindow window(sf::VideoMode(WINX, WINY), "Distributions", sf::Style::Default, settings);
		MyScene scene;

		bool KeyShift = false;
		bool KeyCtrl = false;
		bool KeyAlt = false;
		uint16_t sample_size = 0;
		enum display_type
		{
			none = 0,
			main1,
			main2,
			mixed,
			empirical
		};
		uint16_t display_mode_prev = display_type::none;
		uint16_t display_mode = display_type::none;

		auto update_scene = [&main_distr1, &main_distr2, &mixed_distr, &empirical_distr, &scene, &sample_size, &display_mode, &display_mode_prev]()
		{
			size_t dots_size = pow(100, sample_size - 1) > 1e6 ? static_cast<size_t>(1e6) : static_cast<size_t>(pow(100, sample_size - 1));

			Dots dots(dots_size);
			LineStrip lineStrip(WINX + 1);
			Intervals intervals(0);

			for (int i = 0; i <= WINX; ++i)
			{
				lineStrip.X[i] = static_cast<double>(i) * 5 / WINX;
			}

			switch (display_mode)
			{
			case display_type::main1:
			{
				double Y_size = main_distr1.get_density(main_distr1.get_expected_value());

				for (int i = 0; i <= WINX; ++i)
				{
					lineStrip.Y[i] = main_distr1.get_density(lineStrip.X[i]);
				}
				scene.set_plot(lineStrip, 5. / XCELLS, Y_size / YCELLS);

				scene.set_plot(intervals);

				for (int i = 0; i < dots_size; ++i)
				{
					dots.X[i] = main_distr1.generate_value();
					dots.Y[i] = main_distr1.get_density(dots.X[i]);
				}
				scene.set_dots(dots, 5. / XCELLS, Y_size / YCELLS);

				break;
			}
			case display_type::main2:
			{
				double Y_size = main_distr2.get_density(main_distr2.get_expected_value());

				for (int i = 0; i <= WINX; ++i)
				{
					lineStrip.Y[i] = main_distr2.get_density(lineStrip.X[i]);
				}
				scene.set_plot(lineStrip, 5. / XCELLS, Y_size / YCELLS);

				scene.set_plot(intervals);

				for (int i = 0; i < dots_size; ++i)
				{
					dots.X[i] = main_distr2.generate_value();
					dots.Y[i] = main_distr2.get_density(dots.X[i]);
				}
				scene.set_dots(dots, 5. / XCELLS, Y_size / YCELLS);

				break;
			}
			case display_type::mixed:
			{
				double Y_size = 0;

				for (int i = 0; i <= WINX; ++i)
				{
					lineStrip.Y[i] = mixed_distr.get_density(lineStrip.X[i]);
					if (lineStrip.Y[i] > Y_size)
						Y_size = lineStrip.Y[i];
				}
				scene.set_plot(lineStrip, 5. / XCELLS, Y_size / YCELLS);

				scene.set_plot(intervals);

				for (int i = 0; i < dots_size; ++i)
				{
					dots.X[i] = mixed_distr.generate_value();
					dots.Y[i] = mixed_distr.get_density(dots.X[i]);
				}
				scene.set_dots(dots, 5. / XCELLS, Y_size / YCELLS);

				break;
			}
			case display_type::empirical:
			{
				switch (display_mode_prev)
				{
				case display_type::none:
				{
					double Y_size = 0;

					for (int i = 0; i <= WINX; ++i)
					{
						lineStrip.Y[i] = empirical_distr.get_density(lineStrip.X[i]);
						if (lineStrip.Y[i] > Y_size)
							Y_size = lineStrip.Y[i];
					}
					scene.set_plot(lineStrip, 5. / XCELLS, Y_size / YCELLS);

					scene.set_plot(intervals);

					for (int i = 0; i < dots_size; ++i)
					{
						dots.X[i] = empirical_distr.generate_value();
						dots.Y[i] = empirical_distr.get_density(dots.X[i]);
					}
					scene.set_dots(dots, 5. / XCELLS, Y_size / YCELLS);

					break;
				}
				case display_type::main1:
				{
					double Y_size = 0;

					for (int i = 0; i <= WINX; ++i)
					{
						lineStrip.Y[i] = main_distr1.get_density(lineStrip.X[i]);
						if (lineStrip.Y[i] > Y_size)
							Y_size = lineStrip.Y[i];
					}
					scene.set_plot(lineStrip, 5. / XCELLS, Y_size / YCELLS);

					empirical_distr = EmpiricalDistribution(pow(10, sample_size + 1), main_distr1, empirical_distr.get_k());

					Intervals intervals(empirical_distr.get_k());

					for (size_t i = 0; i < intervals.size; ++i)
					{
						auto interval = empirical_distr.get_interval(i);
						intervals.Xinterval[i].first = interval.first.first;
						intervals.Xinterval[i].second = interval.first.second;
						intervals.Y[i] = interval.second;
						if (intervals.Y[i] > Y_size)
							Y_size = intervals.Y[i];
					}
					scene.set_plot(intervals, 5. / XCELLS, Y_size / YCELLS);

					for (int i = 0; i < dots_size; ++i)
					{
						dots.X[i] = empirical_distr.generate_value();
						dots.Y[i] = empirical_distr.get_density(dots.X[i]);
					}
					scene.set_dots(dots, 5. / XCELLS, Y_size / YCELLS);

					break;
				}
				case display_type::main2:
				{
					double Y_size = 0;

					for (int i = 0; i <= WINX; ++i)
					{
						lineStrip.Y[i] = main_distr2.get_density(lineStrip.X[i]);
						if (lineStrip.Y[i] > Y_size)
							Y_size = lineStrip.Y[i];
					}
					scene.set_plot(lineStrip, 5. / XCELLS, Y_size / YCELLS);

					empirical_distr = EmpiricalDistribution(pow(10, sample_size + 1), main_distr2, empirical_distr.get_k());

					Intervals intervals(empirical_distr.get_k());

					for (size_t i = 0; i < intervals.size; ++i)
					{
						auto interval = empirical_distr.get_interval(i);
						intervals.Xinterval[i].first = interval.first.first;
						intervals.Xinterval[i].second = interval.first.second;
						intervals.Y[i] = interval.second;
						if (intervals.Y[i] > Y_size)
							Y_size = intervals.Y[i];
					}
					scene.set_plot(intervals, 5. / XCELLS, Y_size / YCELLS);

					for (int i = 0; i < dots_size; ++i)
					{
						dots.X[i] = empirical_distr.generate_value();
						dots.Y[i] = empirical_distr.get_density(dots.X[i]);
					}
					scene.set_dots(dots, 5. / XCELLS, Y_size / YCELLS);

					break;
				}
				case display_type::mixed:
				{
					double Y_size = 0;

					for (int i = 0; i <= WINX; ++i)
					{
						lineStrip.Y[i] = mixed_distr.get_density(lineStrip.X[i]);
						if (lineStrip.Y[i] > Y_size)
							Y_size = lineStrip.Y[i];
					}
					scene.set_plot(lineStrip, 5. / XCELLS, Y_size / YCELLS);

					empirical_distr = EmpiricalDistribution(pow(10, sample_size + 1), mixed_distr, empirical_distr.get_k());

					Intervals intervals(empirical_distr.get_k());

					for (size_t i = 0; i < intervals.size; ++i)
					{
						auto interval = empirical_distr.get_interval(i);
						intervals.Xinterval[i].first = interval.first.first;
						intervals.Xinterval[i].second = interval.first.second;
						intervals.Y[i] = interval.second;
						if (intervals.Y[i] > Y_size)
							Y_size = intervals.Y[i];
					}
					scene.set_plot(intervals, 5. / XCELLS, Y_size / YCELLS);

					for (int i = 0; i < dots_size; ++i)
					{
						dots.X[i] = empirical_distr.generate_value();
						dots.Y[i] = empirical_distr.get_density(dots.X[i]);
					}
					scene.set_dots(dots, 5. / XCELLS, Y_size / YCELLS);

					break;
				}
				case display_type::empirical:
				{
					double Y_size = 0;

					for (int i = 0; i <= WINX; ++i)
					{
						lineStrip.Y[i] = empirical_distr.get_density(lineStrip.X[i]);
						if (lineStrip.Y[i] > Y_size)
							Y_size = lineStrip.Y[i];
					}
					scene.set_plot(lineStrip, 5. / XCELLS, Y_size / YCELLS);

					empirical_distr = EmpiricalDistribution(pow(10, sample_size + 1), empirical_distr, empirical_distr.get_k());

					Intervals intervals(empirical_distr.get_k());

					for (size_t i = 0; i < intervals.size; ++i)
					{
						auto interval = empirical_distr.get_interval(i);
						intervals.Xinterval[i].first = interval.first.first;
						intervals.Xinterval[i].second = interval.first.second;
						intervals.Y[i] = interval.second;
						if (intervals.Y[i] > Y_size)
							Y_size = intervals.Y[i];
					}
					scene.set_plot(intervals, 5. / XCELLS, Y_size / YCELLS);

					for (int i = 0; i < dots_size; ++i)
					{
						dots.X[i] = empirical_distr.generate_value();
						dots.Y[i] = empirical_distr.get_density(dots.X[i]);
					}
					scene.set_dots(dots, 5. / XCELLS, Y_size / YCELLS);

					break;
				}
				default:
					break;
				}

				display_mode_prev = display_type::none;
			}
			default:
				break;
			}
		};

		//load saves
		try
		{
			main_distr1.load_from_file("./save1.maindistr");
			if (display_mode == display_type::none)
			{
				display_mode = display_type::main1;
			}
		}
		catch (std::string err)
		{
			std::cout << err << std::endl;
		}

		try
		{
			main_distr2.load_from_file("./save2.maindistr");
			if (display_mode == display_type::none)
			{
				display_mode = display_type::main2;
			}
		}
		catch (std::string err)
		{
			std::cout << err << std::endl;
		}

		try
		{
			mixed_distr.load_from_file("./save.mixeddistr");
			if (display_mode == display_type::none)
			{
				display_mode = display_type::mixed;
			}
		}
		catch (std::string err)
		{
			std::cout << err << std::endl;
		}

		try
		{
			empirical_distr.load_from_file("./save.empiricaldistr");
			if (display_mode == display_type::none)
			{
				display_mode = display_type::empirical;
			}
		}
		catch (std::string err)
		{
			std::cout << err << std::endl;
		}

		update_scene();

		//main loop
		while (window.isOpen())
		{
			window.clear(sf::Color(0xf0, 0xf0, 0xf0));

			sf::Event event;
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
				{
					window.close();
					break;
				}
				case sf::Event::KeyPressed:
				{
					if (event.key.code == sf::Keyboard::Escape)
					{
						window.close();
						break;
					}

					if (event.key.code == sf::Keyboard::Enter)
					{
						switch (display_mode)
						{
						case display_type::main1:
						{
							std::cout << "Expected value: " << main_distr1.get_expected_value() << std::endl;
							std::cout << "Dispersion: " << main_distr1.get_dispersion() << std::endl;
							std::cout << "Skewness: " << main_distr1.get_skewness() << std::endl;
							std::cout << "Kurtosis: " << main_distr1.get_kurtosis() << std::endl << std::endl;
							break;
						}
						case display_type::main2:
						{
							std::cout << "Expected value: " << main_distr2.get_expected_value() << std::endl;
							std::cout << "Dispersion: " << main_distr2.get_dispersion() << std::endl;
							std::cout << "Skewness: " << main_distr2.get_skewness() << std::endl;
							std::cout << "Kurtosis: " << main_distr2.get_kurtosis() << std::endl << std::endl;
							break;
						}
						case display_type::mixed:
						{
							std::cout << "Expected value: " << mixed_distr.get_expected_value() << std::endl;
							std::cout << "Dispersion: " << mixed_distr.get_dispersion() << std::endl;
							std::cout << "Skewness: " << mixed_distr.get_skewness() << std::endl;
							std::cout << "Kurtosis: " << mixed_distr.get_kurtosis() << std::endl << std::endl;
							break;
						}
						case display_type::empirical:
						{
							std::cout << "Expected value: " << empirical_distr.get_expected_value() << std::endl;
							std::cout << "Dispersion: " << empirical_distr.get_dispersion() << std::endl;
							std::cout << "Skewness: " << empirical_distr.get_skewness() << std::endl;
							std::cout << "Kurtosis: " << empirical_distr.get_kurtosis() << std::endl;
							std::cout << "N: " << empirical_distr.get_n() << std::endl;
							std::cout << "K: " << empirical_distr.get_k() << std::endl << std::endl;
							break;
						}
						default:
							break;
						}
					}

					if (event.key.code == sf::Keyboard::F5)
					{
						main_distr1.save_to_file("./save1.maindistr");
						main_distr2.save_to_file("./save2.maindistr");
						mixed_distr.save_to_file("./save.mixeddistr");
						empirical_distr.save_to_file("./save.empiricaldistr");
					}

					if (event.key.code == sf::Keyboard::F9)
					{
						try
						{
							main_distr1.load_from_file("./save1.maindistr");
						}
						catch (std::string err)
						{
							std::cout << err << std::endl;
						}

						try
						{
							main_distr2.load_from_file("./save2.maindistr");
						}
						catch (std::string err)
						{
							std::cout << err << std::endl;
						}

						try
						{
							mixed_distr.load_from_file("./save.mixeddistr");
						}
						catch (std::string err)
						{
							std::cout << err << std::endl;
						}

						try
						{
							empirical_distr.load_from_file("./save.empiricaldistr");
						}
						catch (std::string err)
						{
							std::cout << err << std::endl;
						}

						update_scene();
					}

					if (event.key.code >= sf::Keyboard::Num0 && event.key.code <= sf::Keyboard::Num4)
					{
						if (display_mode == display_type::none)
						{
							display_mode = main1;
						}
						sample_size = event.key.code - 26;
						update_scene();
					}

					if (event.key.code == sf::Keyboard::Q)
					{
						if (KeyAlt)
						{
							display_mode_prev = main1;
							display_mode = empirical;
						}
						else
						{
							display_mode = main1;
						}
						update_scene();
					}
					if (event.key.code == sf::Keyboard::W)
					{
						if (KeyAlt)
						{
							display_mode_prev = main2;
							display_mode = empirical;
						}
						else
						{
							display_mode = main2;
						}
						update_scene();
					}
					if (event.key.code == sf::Keyboard::E)
					{
						if (KeyAlt)
						{
							display_mode_prev = mixed;
							display_mode = empirical;
						}
						else
						{
							display_mode = mixed;
						}
						update_scene();
					}
					if (event.key.code == sf::Keyboard::R)
					{
						if (KeyAlt)
						{
							display_mode_prev = empirical;
							display_mode = empirical;
						}
						else
						{
							display_mode = empirical;
						}
						update_scene();
					}

					if (event.key.code == sf::Keyboard::LShift)
					{
						KeyShift = true;
					}
					if (event.key.code == sf::Keyboard::LControl)
					{
						KeyCtrl = true;
					}
					if (event.key.code == sf::Keyboard::LAlt)
					{
						KeyAlt = true;
					}

					break;
				}
				case sf::Event::KeyReleased:
				{
					if (event.key.code == sf::Keyboard::LShift)
					{
						KeyShift = false;
					}
					if (event.key.code == sf::Keyboard::LControl)
					{
						KeyCtrl = false;
					}
					if (event.key.code == sf::Keyboard::LAlt)
					{
						KeyAlt = false;
					}

					break;
				}
				case sf::Event::MouseWheelScrolled:
				{
					switch (display_mode)
					{
					case display_type::main1:
					{
						if (!KeyShift && !KeyCtrl)
						{
							double new_v = 0.1 * event.mouseWheelScroll.delta + main_distr1.get_v();
							if (new_v < 0)
							{
								new_v = 0;
							}

							std::cout << "v1: " << new_v << '\n';
							main_distr1.set_v(new_v);
						}
						if (KeyShift)
						{
							double new_u = 0.1 * event.mouseWheelScroll.delta + main_distr1.get_u();
							if (new_u < 0)
							{
								new_u = 0;
							}
							if (new_u > 5)
							{
								new_u = 5;
							}

							std::cout << "u1: " << new_u << '\n';
							main_distr1.set_u(new_u);
						}
						if (KeyCtrl)
						{
							double new_l = 0.05 * event.mouseWheelScroll.delta + main_distr1.get_l();
							if (new_l < EPS)
							{
								new_l = EPS;
							}

							std::cout << "l1: " << new_l << '\n';
							main_distr1.set_l(new_l);
						}
						break;
					}
					case display_type::main2:
					{
						if (!KeyShift && !KeyCtrl)
						{
							double new_v = 0.1 * event.mouseWheelScroll.delta + main_distr2.get_v();
							if (new_v < 0)
							{
								new_v = 0;
							}

							std::cout << "v2: " << new_v << '\n';
							main_distr2.set_v(new_v);
						}
						if (KeyShift)
						{
							double new_u = 0.1 * event.mouseWheelScroll.delta + main_distr2.get_u();
							if (new_u < 0)
							{
								new_u = 0;
							}
							if (new_u > 5)
							{
								new_u = 5;
							}

							std::cout << "u2: " << new_u << '\n';
							main_distr2.set_u(new_u);
						}
						if (KeyCtrl)
						{
							double new_l = 0.05 * event.mouseWheelScroll.delta + main_distr2.get_l();
							if (new_l < EPS)
							{
								new_l = EPS;
							}

							std::cout << "l2: " << new_l << '\n';
							main_distr2.set_l(new_l);
						}
						break;
					}
					case display_type::mixed:
					{
						if (KeyShift && KeyCtrl)
						{
							double new_p = 0.05 * event.mouseWheelScroll.delta + mixed_distr.get_p();
							if (new_p < 0)
							{
								new_p = 0;
							}
							if (new_p > 1)
							{
								new_p = 1;
							}
							std::cout << "p: " << new_p << '\n';
							mixed_distr.set_p(new_p);

							break;
						}
						if (!KeyShift && !KeyCtrl)
						{
							if (!KeyAlt)
							{
								double new_v = 0.1 * event.mouseWheelScroll.delta + mixed_distr.component1().get_v();
								if (new_v < 0)
								{
									new_v = 0;
								}
								std::cout << "vM1: " << new_v << '\n';
								mixed_distr.component1().set_v(new_v);
							}
							else
							{
								double new_v = 0.1 * event.mouseWheelScroll.delta + mixed_distr.component2().get_v();
								if (new_v < 0)
								{
									new_v = 0;
								}
								std::cout << "vM2: " << new_v << '\n';
								mixed_distr.component2().set_v(new_v);
							}
						}
						if (KeyShift)
						{

							if (!KeyAlt)
							{
								double new_u = 0.1 * event.mouseWheelScroll.delta + mixed_distr.component1().get_u();
								if (new_u < 0)
								{
									new_u = 0;
								}
								if (new_u > 5)
								{
									new_u = 5;
								}
								std::cout << "uM1: " << new_u << '\n';
								mixed_distr.component1().set_u(new_u);
							}
							else
							{
								double new_u = 0.1 * event.mouseWheelScroll.delta + mixed_distr.component2().get_u();
								if (new_u < 0)
								{
									new_u = 0;
								}
								if (new_u > 5)
								{
									new_u = 5;
								}
								std::cout << "uM2: " << new_u << '\n';
								mixed_distr.component2().set_u(new_u);
							}
						}
						if (KeyCtrl)
						{
							if (!KeyAlt)
							{
								double new_l = 0.05 * event.mouseWheelScroll.delta + mixed_distr.component1().get_l();
								if (new_l < EPS)
								{
									new_l = EPS;
								}
								std::cout << "lM1: " << new_l << '\n';
								mixed_distr.component1().set_l(new_l);
							}
							else
							{
								double new_l = 0.05 * event.mouseWheelScroll.delta + mixed_distr.component2().get_l();
								if (new_l < EPS)
								{
									new_l = EPS;
								}
								std::cout << "lM2: " << new_l << '\n';
								mixed_distr.component2().set_l(new_l);
							}
						}
						break;
					}
					case display_type::empirical:
					{
						size_t new_k = event.mouseWheelScroll.delta + empirical_distr.get_k();
						if (new_k < 2)
						{
							new_k = 2;
						}
						if (new_k > MAXINTERVALS)
						{
							new_k = MAXINTERVALS;
						}

						std::cout << "k: " << new_k << '\n';
						empirical_distr.set_k(new_k);
						break;
					}
					default:
						break;
					}

					update_scene();

					break;
				}
				}
			}

			scene.draw(window);
			window.display();
		}
	}
	catch (std::string err)
	{
		std::cout << err << std::endl;
	}

	return 0;
}