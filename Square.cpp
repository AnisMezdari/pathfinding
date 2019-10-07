#include "Square.h"
#include "Terrain.h"
#include <list> 

Square::Square() {
	this->width = 0;
	this->height = 0;

}

Square::Square(float width, float height, bool obstacle, float poid)
{
	this->width = width;
	this->height = height;
	this->obstacle = obstacle;
	this->poid = poid;
	this->poid = poid;
}


bool Square::compare(Square otherSquare) {
	return getDistance(otherSquare) == 0;
}

float Square::getDistance(Square otherSquare) {
	return std::abs(this->positionX - otherSquare.positionX) + std::abs(this->positionY - otherSquare.positionY);
}

void Square::setPositionSquare(int width, int height ) {
	this->positionX_square = (int) (((this->positionX) / width) );
	//std::cout << positionY_square << "\n";
	this->positionY_square = (int) (((this->positionY ) / height) );
}


std::list<Square> Square::getVoisins(Terrain terrain) {

	std::list<Square> listSquare;
 	std::list<std::list<Square>>::iterator it = std::next(terrain.tabSquare.begin(), this->positionX_square);
	if ((this->positionY_square + 1 >= terrain.height )== 1) {
		//std::cout << "\n" << (this->positionY_square + 1);
		for (auto it_n = it->begin(); it_n != it->end(); ++it_n) {
			//std::cout << it_n->positionX_square << " " << it_n->positionY_square << "\n";
		}
		//std::cout << (this->positionY_square + 1);
		std::list<Square>::iterator it2 = std::next(it->begin(), (this->positionY_square + 1));
		listSquare.push_front(*it2);
	}
	
	std::list<std::list<Square>>::iterator it_1 = std::next(terrain.tabSquare.begin(), this->positionX_square);
	if (!(this->positionY_square - 1 < 0)) {
		std::list<Square>::iterator it2_1 = std::next(it->begin(), (this->positionY_square - 1));
		if (&it2_1 != NULL) {
			listSquare.push_front(*it2_1);
		}
	}
	
	if (!(this->positionX_square + 1 >= terrain.width)) {
		std::list<std::list<Square>>::iterator it_2 = std::next(terrain.tabSquare.begin(), this->positionX_square + 1);
		std::list<Square>::iterator it2_2 = std::next(it->begin(), this->positionY_square);
		if (&it2_2 != NULL) {
			listSquare.push_front(*it2_2);
		}
	}
	if (!(this->positionX_square + 1 >= terrain.width)) {
		std::list<std::list<Square>>::iterator it_3 = std::next(terrain.tabSquare.begin(), this->positionX_square + 1);
		if (!(this->positionY_square - 1 < 0)) {
			std::list<Square>::iterator it2_3 = std::next(it->begin(), (this->positionY_square - 1));
			if (&it2_3 != NULL) {
				listSquare.push_front(*it2_3);
			}
		}
	}

	if (!(this->positionX_square + 1 >= terrain.width)) {
		std::list<std::list<Square>>::iterator it_4 = std::next(terrain.tabSquare.begin(), (this->positionX_square + 1));
		if (!(this->positionY_square + 1 >= terrain.height)) {

			std::list<Square>::iterator it2_4 = std::next(it->begin(), (this->positionY_square + 1));
			if (&it2_4 != NULL) {
				listSquare.push_front(*it2_4);
			}
		}
	}

	if (!(this->positionX_square - 1 < 0)) {
		std::list<std::list<Square>>::iterator it_5 = std::next(terrain.tabSquare.begin(), (this->positionX_square - 1));
		if (!(this->positionY_square + 1 >=  terrain.height)) {
			std::list<Square>::iterator it2_5 = std::next(it->begin(), (this->positionY_square + 1));
			if (&it2_5 != NULL) {
				listSquare.push_front(*it2_5);
			}
		}
	}

	if (!(this->positionX_square - 1 < 0)) {
		std::list<std::list<Square>>::iterator it_6 = std::next(terrain.tabSquare.begin(),( this->positionX_square - 1));
		std::list<Square>::iterator it2_6 = std::next(it->begin(), this->positionY_square);
		if (&it2_6 != NULL) {
			listSquare.push_front(*it2_6);
		}
	}
	if (!(this->positionX_square - 1 < 0)) {
		std::list<std::list<Square>>::iterator it_7 = std::next(terrain.tabSquare.begin(), (this->positionX_square - 1));
		if (!(this->positionY_square - 1 < 0)) {
			std::list<Square>::iterator it2_7 = std::next(it->begin(), (this->positionY_square - 1));
			if (&it2_7 != NULL) {
				listSquare.push_front(*it2_7);
			}
		}
	}
	return listSquare;

}

bool operator==(const Square& a, const Square& b)
{
	float dx = a.positionX - b.positionX;
	float dy = a.positionY - b.positionY;
	return ((dx * dx) + (dy * dy)) < 0.0000001f;
}

bool operator!=(const Square& a, const Square& b)
{
	return !(a == b);
}
