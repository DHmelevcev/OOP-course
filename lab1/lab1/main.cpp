#include "main_distribution.h"
#include "mixture_distibution.h"
#include "empirical_distribution.h"
#include "tests.h"
#include "../../UI/scene.h"
#include <iostream>

int main()
{
	srand(time(0));

	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;
	sf::RenderWindow window(sf::VideoMode(WINX, WINY), "Distributions", sf::Style::Default, settings);
	MyScene scene;

	test::main_distribution_density();
	test::main_distribution_transforms();
	test::mix_distribution_density();
	test::mix_distribution_expected_value();
	test::mix_distribution_dispersion();

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

				if (event.key.code >= sf::Keyboard::Num1 && event.key.code <= sf::Keyboard::Num7)
				{
					system("cls");
					test::main_distribution_density();
					test::main_distribution_transforms();
					test::mix_distribution_density();
					test::mix_distribution_expected_value();
					test::mix_distribution_dispersion();
					test::emp_distribution(event.key.code - 26, scene);
				}

				break;
			}
			}
		}

		scene.draw(window);
		window.display();
	}

	return 0;
}