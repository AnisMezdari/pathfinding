#pragma once
class Square
{
public:
	float width;
	float height;
	float positionX;
	float positionY;
	bool obstacle;

	Square();
	Square(float width , float height, bool obstacle);
};

