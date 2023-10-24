#include "main_distribution.h"
#include "tests.h"
#include "../../UI/scene.h"
#include <iostream>
#include <time.h>

#ifndef EPS
#define EPS 0.5e-1
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
	}
	catch (std::string err)
	{
		std::cout << err << std::endl;
	}

	try
	{
		double v = 1, u = 2.5, l = 1;
		MainDistribution main_distr(v, u, l);

		sf::ContextSettings settings;
		settings.antialiasingLevel = 4;
		sf::RenderWindow window(sf::VideoMode(WINX, WINY), "Distributions", sf::Style::Default, settings);
		MyScene scene;

		bool KeyShift = false;
		bool KeyCtrl = false;
		sf::Keyboard::Key lastKey = sf::Keyboard::Unknown;

		auto update_scene = [&main_distr, &scene, &lastKey]()
		{
			size_t dots_size = pow(100, lastKey - 27) > 1e6 ? static_cast<size_t>(1e6) : static_cast<size_t>(pow(100, lastKey - 27));

			Dots dots(dots_size);
			for (int i = 0; i < dots_size; i++)
			{
				dots.X[i] = main_distr.generate_value();
				dots.Y[i] = main_distr.get_density(dots.X[i]);
			}
			scene.set_dots(dots, 5. / XCELLS, main_distr.get_density(main_distr.get_expected_value()) / YCELLS);

			LineStrip lineStrip(WINX + 1);
			for (int i = 0; i <= WINX; i++)
			{
				lineStrip.X[i] = static_cast<double>(i) * 5 / WINX;
				lineStrip.Y[i] = main_distr.get_density(lineStrip.X[i]);
			}
			scene.set_plot(lineStrip, 5. / XCELLS, main_distr.get_density(main_distr.get_expected_value()) / YCELLS);
		};

		try
		{
			main_distr.load_from_file("./save.distr");
			lastKey = sf::Keyboard::Num0;
			v = main_distr.get_v();
			u = main_distr.get_u();
			l = main_distr.get_l();
			update_scene();
		}
		catch (std::string err)
		{
			std::cout << err << std::endl;
		}

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

					if (event.key.code == sf::Keyboard::F5)
					{
						main_distr.save_to_file("./save.distr");
					}

					if (event.key.code == sf::Keyboard::F9)
					{
						try
						{
							main_distr.load_from_file("./save.distr");
							if (lastKey == sf::Keyboard::Unknown)
								lastKey = sf::Keyboard::Num0;
							v = main_distr.get_v();
							u = main_distr.get_u();
							l = main_distr.get_l();
							update_scene();
						}
						catch (std::string err)
						{
							std::cout << err << std::endl;
						}
					}

					if (event.key.code >= sf::Keyboard::Num0 && event.key.code <= sf::Keyboard::Num3)
					{
						lastKey = event.key.code;
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

					break;
				}
				case sf::Event::MouseWheelScrolled:
				{
					if (!KeyShift && !KeyCtrl)
					{
						double new_v = 0.1 * event.mouseWheelScroll.delta + v;
						if (new_v < 0)
						{
							new_v = 0;
						}

						v = new_v;
						std::cout << "v: " << v << '\n';
						main_distr.set_v(v);
						if (lastKey != sf::Keyboard::Unknown)
							update_scene();
					}
					if (KeyShift)
					{
						double new_u = 0.1 * event.mouseWheelScroll.delta + u;
						if (new_u < 0)
						{
							new_u = 0;
						}
						if (new_u > 5)
						{
							new_u = 5;
						}

						u = new_u;
						std::cout << "u: " << u << '\n';
						main_distr.set_u(u);
						if (lastKey != sf::Keyboard::Unknown)
							update_scene();
					}
					if (KeyCtrl)
					{
						double new_l = 0.05 * event.mouseWheelScroll.delta + l;
						if (new_l < EPS)
						{
							new_l = EPS;
						}

						l = new_l;
						std::cout << "l: " << l << '\n';
						main_distr.set_l(l);
						if (lastKey != sf::Keyboard::Unknown)
							update_scene();
					}

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