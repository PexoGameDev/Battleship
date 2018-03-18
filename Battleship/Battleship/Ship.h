#pragma once
#include "vector"

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

void Ship::Draw()
{
	for (int i = 0; i < body.size(); i++)
	{
		body[i].field.setFillColor(sf::Color(255, 50, 50));
		Game::Window().draw(body[i].field);
	}
}