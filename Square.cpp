#include "Square.h"
Square::Square() {

}

Square::Square(float width, float height, bool obstacle, float poid)
{
	this->width = width;
	this->height = height;
	this->obstacle = obstacle;
	this->poid = poid;
}
