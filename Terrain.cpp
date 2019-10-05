#include "Terrain.h"
#include <chrono>
#include <thread>
#include <random>

Terrain::Terrain(int width, int height, float widthSquare , float heightSquare ) {
	srand(time(NULL));
	
	for (int i = 0; i < width; i++) {
		std::list<Square> listSquare_h;
		for (int j = 0; j < height; j++) {
			int randNum = std::rand() % 5 + 1;
			if (randNum == 5) {
				Square square(widthSquare, heightSquare, true);
				square.positionX = 3 + (widthSquare * i);
				square.positionY = 3 + (heightSquare * j);
				listSquare_h.push_back(square);
			}
			else {
				Square square(widthSquare, heightSquare, false);
				square.positionX = 3 + (widthSquare * i);
				square.positionY = 3 + (heightSquare * j);
				listSquare_h.push_back(square);
			}
		}
		this->tabSquare.push_back(listSquare_h);
	}
}

