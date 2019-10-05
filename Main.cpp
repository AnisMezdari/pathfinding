#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>
#include <time.h>  
#include <chrono>
#include <thread>
#include "Terrain.h"
#include <list> 

int main()
{
	sf::RenderWindow window(sf::VideoMode(1250, 750), "Jeu vidéo incroyable");


	// Terrain generation
	int width = 24;
	int height = 14;
	float widthSquare = 50;
	float heightSquare = 50;
	Terrain terrain(width, height, widthSquare, heightSquare);

	std::list< std::list<sf::RectangleShape>> listSquareView_2d;
	for (std::list< std::list<Square>> ::iterator widthTerrain = terrain.tabSquare.begin(); widthTerrain != terrain.tabSquare.end(); ++widthTerrain) {
		std::list<sf::RectangleShape> listSquareView;
		for (std::list<Square>::iterator heightTerrain = widthTerrain->begin(); heightTerrain != widthTerrain->end(); ++heightTerrain) {

			sf::RectangleShape  rectangle(sf::Vector2f(heightTerrain->width, heightTerrain->height));
			rectangle.setPosition(heightTerrain->positionX, heightTerrain->positionY);
			rectangle.setOutlineThickness(2.f);
			rectangle.setOutlineColor(sf::Color(0, 0, 0));
			if (heightTerrain->obstacle) {
				rectangle.setFillColor(sf::Color(0, 0, 0));
			}
			else {
				rectangle.setFillColor(sf::Color(255, 255, 255));
			}
			listSquareView.push_back(rectangle);
		
		}
		listSquareView_2d.push_back(listSquareView);
	
	}
	// Character
	sf::CircleShape shape(10.f);
	shape.setFillColor(sf::Color(70, 130, 180));
	shape.setPosition(15, 15);


	// Frame loop
	int p = 1;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear(sf::Color(220, 220, 220, 50));
		for (std::list< std::list<sf::RectangleShape>> ::iterator listSquareView_2d_w = listSquareView_2d.begin(); listSquareView_2d_w != listSquareView_2d.end(); ++listSquareView_2d_w) {
			for (std::list<sf::RectangleShape>::iterator listSquareView_2d_h = listSquareView_2d_w->begin(); listSquareView_2d_h != listSquareView_2d_w->end(); ++listSquareView_2d_h) {
				window.draw(*listSquareView_2d_h);
			}

		}
		window.draw(shape);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		shape.setPosition(15 + (p * 50),15 + (p * 50));
		p++;
		window.display();
	}
	
	return 0;
}