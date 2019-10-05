#pragma once

#include <iostream> 
#include <list> 
#include <iterator>
#include "Square.h"

class Terrain
{
public:
	int width;
	int height;
	float widthSquare;
	float heightSquare;
	std::list< std::list<Square>> tabSquare;
	//Square tabSquare[1][1];
	Terrain(int width, int height,float widthSquare, float heightSquare);

};

