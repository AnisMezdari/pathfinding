#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "Jeu vidéo incroyable");
	
	sf::CircleShape shape(100.f);
	sf::CircleShape square(80.f, 4);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color(220, 220, 220, 50));
		window.draw(shape);
		window.draw(square);
		window.display();
	}

	return 0;
}