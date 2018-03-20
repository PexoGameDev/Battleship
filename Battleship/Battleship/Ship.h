#pragma once
#include "vector"
#include "Game.h"

class Ship
{
private:
	std::vector<MapField> body;
public:
	Ship(std::vector<MapField> fields);
	~Ship();
	void Draw();
};

Ship::Ship(std::vector<MapField> fields)
{
	Ship::body = fields;
}

Ship::~Ship()
{

}
