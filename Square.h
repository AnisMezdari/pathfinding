#pragma once
#include <list> 
class Terrain;

class Square
{
public:
	float width;
	float height;
	float positionX;
	float positionY;

	int positionX_square;
	int positionY_square;
	bool obstacle;
	float poid;

	Square();
	Square(float width, float height, bool obstacle, float poid);
	bool compare(Square otherSquare);
	std::list<Square> getVoisins(Terrain terrain);
	float getDistance(Square otherSquare);
	void setPositionSquare(int width, int height);

};


bool operator==(const Square& a, const Square& b);
bool operator!=(const Square& a, const Square& b);
