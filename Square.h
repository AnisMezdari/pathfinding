#pragma once
class Square
{
public:
	float width;
	float height;
	float positionX;
	float positionY;
	bool obstacle;
	float poid;

	Square();
	Square(float width, float height, bool obstacle, float poid);
};

