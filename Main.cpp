#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>
#include <time.h>  
#include <chrono>
#include <thread>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1250, 750), "Jeu vidéo incroyable");
	
	srand(time(NULL));
	sf::RectangleShape listRectangle[20][10];
	sf::CircleShape shape(10.f);
	shape.setFillColor(sf::Color(70, 130, 180));
	shape.setPosition(15, 15);
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 10; j++) {
			sf::RectangleShape  rectangle(sf::Vector2f(50.f, 50.f));
			rectangle.setPosition(3 +( 50 * i) , 3 +(50 *j ));
			rectangle.setOutlineThickness(2.f);
			rectangle.setOutlineColor(sf::Color(0, 0, 0));
			int randNum = std::rand() % 5 + 1;
			if (randNum == 5) {
				rectangle.setFillColor(sf::Color(0, 0, 0));
			}
			listRectangle[i][j] = rectangle;
		}
	}
	int i = 1;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color(220, 220, 220, 50));
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 10; j++) {
				window.draw(listRectangle[i][j]);
			}
		}
		window.draw(shape);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		shape.setPosition(15 + (i * 50),15 + (i * 50));
		i++;
		window.display();
	}
	
	return 0;
}