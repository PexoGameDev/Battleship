#pragma once
#include "vector"
#include "Game.h"
#include "Map.h"

class Ship
{
public:
	Ship(std::vector<MapField*> fields, int hp);
	~Ship();
	void Sink();
	int HP;
	std::vector<MapField*> body;
	void Hit();
};

Ship::~Ship(){}

Ship::Ship(std::vector<MapField*> fields, int hp)
{
	Ship::body = fields;
	HP = hp;
}

void Ship::Sink()
{
	std::cout << "Im sinking? \n";
	for (int i = 0; i < this->body.size(); i++)
		body[i]->SetState(MapFieldState::sunk);
}

void Ship::Hit()
{
	Ship::HP--;
	std::cout << "I'm hit, hp:" << Ship::HP<<"\n";
	if (HP <= 0)
		Sink();
}