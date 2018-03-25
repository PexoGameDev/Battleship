#pragma once
#include "Map.h"
#include "string"
#include "vector"
#include "Ship.h"
#include "random"
#include "cstdlib"
#include "time.h"

class Player
{
public:
	Player();
	Player(std::string name, int id);
	~Player();
	std::string Name;
	std::vector<Ship> ships;
	int ID;
	int ShipCount = 10;
};

Player::~Player() {}
Player::Player() {}

Player::Player(std::string name, int id)
{
	Player::Name = name;
	Player::ID = id;
	ships = {};
}