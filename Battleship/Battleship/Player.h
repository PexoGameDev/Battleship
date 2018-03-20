#pragma once
#include "string"
#include "vector"
#include "Ship.h"

class Player
{
public:
	Player();
	Player(std::string name);
	~Player();
	std::string Name;
	std::vector<Ship> ships;

private:

};
Player::Player()
{

}
Player::Player(std::string name)
{
	Player::Name = name;
	ships = {};
}

Player::~Player()
{
}