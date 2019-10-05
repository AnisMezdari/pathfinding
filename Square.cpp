#include "Square.h"
Square::Square() {

}

Square::Square(float width, float height, bool obstacle)
{
	this->width = width;
	this->height = height;
	this->obstacle = obstacle;
}
