#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>
#include <time.h>  
#include <chrono>
#include <thread>
#include "Terrain.h"
#include <list> 
#include "Square.h"


std::list< std::list<sf::RectangleShape>> terrainGeneration( Terrain terrain) {
	
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

	return listSquareView_2d;
}


sf::CircleShape  CharacterCreation() {
	sf::CircleShape shape(10.f);
	shape.setFillColor(sf::Color(70, 130, 180));
	shape.setPosition(15, 15);

	return shape;
}

void disjtra(int x, int y, std::list< std::list<int>> matriceSquare) {
	bool pasfini = false;
	std::list<Square> noeud;
	//noeud.push_back(Square(x,y));
	/*while (!noeud.empty) {
		
		std::list< std::list<int>>::iterator it = std::next(matriceSquare.begin(), x);
		for (int j = 0; j < it->size(); j++) {
			std::list<int>::iterator it2 = std::next(it->begin(), j);

			//it2 
		}

	}*/
}


int main()
{
	sf::RenderWindow window(sf::VideoMode(1250, 750), "Jeu vidéo incroyable");

	const int width = 5;
	const int height = 5;
	float widthSquare = 50;
	float heightSquare = 50;
	Terrain terrain(width, height, widthSquare, heightSquare);

	std::list< std::list<sf::RectangleShape>> listSquareView_2d = terrainGeneration(terrain);
	sf::CircleShape character = CharacterCreation();


	std::list< std::list<int>> matriceSquare;

	/*std::list<Square>::iterator it = terrain.SquareDistance.begin();
	std::list<Square>::iterator it2 = terrain.SquareDistance.begin();*/
	for ( int i = 0; i < terrain.SquareDistance.size(); i++) {
		
		std::list<Square>::iterator it = std::next(terrain.SquareDistance.begin(), i);
		std::list<int> listDistance;
		for ( int j = 0; j < terrain.SquareDistance.size(); j++) {
			
			std::list<Square>::iterator it2 = std::next(terrain.SquareDistance.begin(), j);
			
			if (!(it->positionX  == it2->positionX && it->positionY == it2->positionY)) {
				int distance = std::abs(it->positionX - it2->positionX) + std::abs(it->positionY - it2->positionY);
				distance = distance / (int)widthSquare;
				distance = (int) ((distance / 2) + 1);
				distance = distance * it2->poid;
				listDistance.push_back(distance);
				std::cout << "  x :" << (int)((it->positionX-3)/50) << " y :" << (int) ((it->positionY-3)/50 )<< " ////  x : " << (int) ((it2->positionX-3)/50) << " y :" << (int) ((it2->positionY-3)/50) << " Distance : " << distance << "\n";

			} 
			
		}
		matriceSquare.push_back(listDistance);
	}


	/*for (int i = 0; i < matriceSquare.size(); i++) {
		std::list< std::list<int>>::iterator it = std::next(matriceSquare.begin(), i);
		for (int j =  0; j < it->size(); j++) {
			std::list<int>::iterator it2 = std::next(it->begin(), j);
			std::cout << " i:" << i << "  j:" << j <<"   distance :" << *it2 << "\n";
		}
	}*/



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
		window.draw(character);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		character.setPosition(15 + (p * 50),15 + (p * 50));
		p++;
		window.display();
	}
	
	return 0;
}