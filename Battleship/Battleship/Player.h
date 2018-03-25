#pragma once
#include "string"
#include "vector"
#include "Ship.h"
#include "Map.h"

class Player
{
public:
	Player();
	Player(std::string name, int id);
	~Player();
	std::string Name;
	std::vector<Ship> ships;
	int ID;

private:
};
Player::~Player() {}
Player::Player() {}
Player::Player(std::string name, int id)
{
	Player::Name = name;
	Player::ID = id;
	ships = {};
}
