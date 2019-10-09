#pragma once
#include <string>
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


	template <>
	struct std::hash<Square>
	{
		std::size_t operator()(const Square& k) const
		{
			using std::size_t;
			using std::hash;
			using std::string;

			// Compute individual hash values for first,
			// second and third and combine them using XOR
			// and bit shifting:

			return ((hash<int>()((int)k.positionX_square)
				^ (hash<int>()((int)k.positionY_square) << 1)) >> 1);
		}
	};

