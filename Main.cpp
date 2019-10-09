#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>
#include <time.h>  
#include <chrono>
#include <thread>
#include "Terrain.h"
#include <list> 
#include "Square.h"
#include <algorithm>
#include <limits>
#include <unordered_map>

std::list< std::list<sf::RectangleShape>> terrainGeneration(Terrain &terrain) {

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


sf::CircleShape  CharacterCreation(float positionX, float positionY,Terrain &terrain, sf::Color color) {
	sf::CircleShape shape(10.f);
	shape.setFillColor(color);
	shape.setPosition(15 + (positionX * terrain.widthSquare), 15 + (positionY * terrain.heightSquare));

	return shape;
}

sf::CircleShape blackHole(float positionX, float positionY, Terrain &terrain) {
	sf::CircleShape shape(19.f);
	shape.setFillColor(sf::Color(0,0,0));
	shape.setPosition(8 + (positionX * terrain.widthSquare), 8 + (positionY * terrain.heightSquare));

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

std::list<Square> A_star(Square &positionInital, Square &positionFinal, Terrain &terrain) {

	std::list<Square> openList;
	std::list<Square> closeList;
	positionInital.poid = 0;
	openList.push_back(positionInital);
	
	std::list<Square> shortPath;
	std::unordered_map<Square, Square> preceding;
	while (!openList.empty())
	{
		//Find minimum Square
		float min = std::numeric_limits<float>::max();
		std::list<Square>::iterator minSquareIt;		
		for (auto it = openList.begin(); it != openList.end(); ++it) {
			if (it->getDistance(positionInital) + it->getDistance(positionFinal) < min) {
				min = it->getDistance(positionInital) + it->getDistance(positionFinal);
				minSquareIt = it;
				//std::cout << it->positionY_square<<"\n";
			}
		}
		Square minSquare = *minSquareIt;
		//Found the shortest path to the end; exit
		if (minSquare == positionFinal) {
			auto it = preceding.find(minSquare);
			while (it != preceding.end())
			{
				shortPath.push_front(minSquare);
				minSquare = preceding[minSquare];
				it = preceding.find(minSquare);
			}

			//insert the start node in the path
			shortPath.push_front(minSquare);
			return shortPath;
		}
		//Remove from open list
		openList.erase(minSquareIt);
		//add to closed list
		closeList.push_front(minSquare);
				
		std::list<Square> voisin = minSquare.getVoisins(terrain);
		//std::unordered_map<Square, Square> map;

		for (auto it2 = voisin.begin(); it2 != voisin.end(); ++it2) {
			bool inOpenList = std::find(openList.begin(), openList.end(), *it2) != openList.end();
			bool inCloseList = std::find(closeList.begin(), closeList.end(), *it2) != closeList.end();
			if (!inOpenList && !inCloseList && !it2->obstacle) {
				openList.push_front(*it2);
				preceding[*it2] = minSquare;
			}
		}
	}
	return shortPath;
	
}

int randomPostion(bool isPlayer, Terrain &terrain) {
	srand(time(NULL));
	int randNum = 0;
	if (isPlayer) {
		
		std::list<Square>::iterator it;
		do {
			randNum = std::rand() % terrain.height + 1;
			it = std::next(terrain.SquareDistance.begin(), randNum);
			
		} while (it->obstacle);
	}
	else {
		std::list<Square>::iterator it;
		do {
			randNum = (std::rand() % (terrain.height-1) + ((terrain.height * terrain.width) - terrain.height));
			it = std::next(terrain.SquareDistance.begin(), randNum);
		} while (it->obstacle);
	}

	return randNum;
}


sf::CircleShape setPositionBlackHoleByMouse(sf::RenderWindow *window, Terrain &terrain) {
	int x = sf::Mouse::getPosition(*window).x;
	int y = sf::Mouse::getPosition(*window).y;

	//std::cout << x << " " << y << "\n";
	int positionX_blackHole = (x / terrain.widthSquare) ;
	int positionY_blackHole = (y / terrain.heightSquare) ;
	//std::cout << (positionX_blackHole * terrain.widthSquare)  << " " << positionY_blackHole << "\n";

	return blackHole(positionX_blackHole, positionY_blackHole,terrain);

	//blackHole_->setPosition(positionX_blackHole * terrain.widthSquare, positionY_blackHole * terrain.heightSquare);

}

sf::Sprite displayButton(sf::RenderWindow &window) {
	sf::Texture texture;
	if (!texture.loadFromFile("play_button.png"))
	{
		// erreur...
		std::cout << " error";
	}
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setScale(0.1, 0.1);
	sprite.setPosition(5, 15*51);	
	window.draw(sprite);
	return sprite;
}

bool collisionMouseAndButton(int mouseX, int mouseY, int spriteX, int spriteY) {
	if ((mouseX > spriteX && mouseX < (spriteX + 50)) && (mouseY > spriteY && (spriteY + 50))) {
		return true;
	}
	return false;
}


bool  playSimulation(std::list<Square> &shortPath, Terrain &terrain, sf::CircleShape &IA, int &compteur) {

	auto nextPostion = std::next(shortPath.begin(), compteur);

	if (nextPostion != shortPath.end()) {
		IA.setPosition(15 + (nextPostion->positionX_square * terrain.widthSquare), 15 + (nextPostion->positionY_square * terrain.heightSquare));
		std::cout << nextPostion->hasBlackHole << "\n";
		if (nextPostion->hasBlackHole) {
			std::cout << "sa passe";
			return false;
		}
	}
	else {
		return false;
	}
	return true;
}


int main()
{
	sf::RenderWindow window(sf::VideoMode(1250, 850), "Jeu vidéo incroyable");

	const int width = 25;
	const int height = 15;
	float widthSquare = 50;
	float heightSquare = 50;
	Terrain terrain(width, height, widthSquare, heightSquare);

	std::list< std::list<sf::RectangleShape>> listSquareView_2d = terrainGeneration(terrain);
	

	auto  initalPosition = std::next(terrain.SquareDistance.begin(), randomPostion(true,terrain));
	auto finalPostion = std::next(terrain.SquareDistance.begin(), randomPostion(false,terrain));

	
	sf::CircleShape character = CharacterCreation(finalPostion->positionX_square, finalPostion->positionY_square,terrain, sf::Color(70, 130, 180));
	sf::CircleShape IA = CharacterCreation(initalPosition->positionX_square,initalPosition->positionY_square,terrain, sf::Color(178, 34, 34));
	sf::CircleShape blackHole_userInterface = blackHole(1,15,terrain);
	//sf::CircleShape blackHole_ = blackHole(15, 15, terrain);

	std::cout << "\n\n\n\n";
	std::cout << "Initial postition : " << initalPosition->positionX_square << " " << initalPosition->positionY_square << "\n";
	std::cout << "Final postition : " << finalPostion->positionX_square << " " << finalPostion->positionY_square << "\n";
	
	
	
	sf::CircleShape blackHole;
	bool isCliked = false;
	bool play = false;
	int compteur = 0;
	bool setSquare = false;
	std::list<Square> shortPath;
	// Frame loop
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear(sf::Color(220, 220, 220, 50));
		for (auto listSquareView_2d_w = listSquareView_2d.begin(); listSquareView_2d_w != listSquareView_2d.end(); ++listSquareView_2d_w) {
			for (auto listSquareView_2d_h = listSquareView_2d_w->begin(); listSquareView_2d_h != listSquareView_2d_w->end(); ++listSquareView_2d_h) {
				window.draw(*listSquareView_2d_h);
			}
		}

		if (!isCliked) {
			blackHole = setPositionBlackHoleByMouse(&window, terrain);
		}

		window.draw(blackHole);
		window.draw(character);
		sf::Sprite sprite = displayButton(window);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			// left click...
			isCliked = true;
			if (!setSquare) {
				float x =(( blackHole.getPosition().x - 8) / terrain.widthSquare );
				float y = ((blackHole.getPosition().y - 8) / terrain.heightSquare);
				
				for (auto it = terrain.tabSquare.begin(); it != terrain.tabSquare.end(); it++) {
					for (auto it2 = it->begin(); it2 != it->end(); it2++) {
						if (it2->positionX_square == x && it2->positionY_square == y) {
							it2->setBlackHole(true);
						}
					}
				}
				shortPath = A_star(*initalPosition, *finalPostion, terrain);
				setSquare = true;
			}

			if (collisionMouseAndButton(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, sprite.getPosition().x, sprite.getPosition().y)) {
				play = true;
			}
		}
	
		// get global mouse position
		//std::cout << sf::Mouse::getPosition(window).x << " " << sf::Mouse::getPosition(window).y << "\n";
		// set mouse position relative to a window
		//sf::sleep(sf::seconds(0.1f));
		window.draw(IA);
		if (play) {
			sf::sleep(sf::seconds(0.2f));
			play = playSimulation(shortPath, terrain, IA,compteur);
			compteur++;
		}
		
		
		window.display();
		
	}
	
	return 0;
}