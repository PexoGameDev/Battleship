#pragma once
#include "string"

class Player
{
public:
	Player(std::string name, short ships);
	~Player();
	std::string Name;
	short ShipsLeft;
private:

};

Player::Player(std::string name, short ships)
{
	Player::Name = name;
	Player::ShipsLeft = ships;
}

Player::~Player()
{
}