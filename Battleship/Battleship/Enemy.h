#pragma once
#include "Player.h"
#include "Map.h"
#include "SFML/Graphics.hpp"
#include "random"
#include "cstdlib"
#include "time.h"

class Enemy : Player
{
public:
	Enemy();
	Enemy(std::string name, int id);
	~Enemy();
	std::string Name;
	Map* RandomizeShips();
	std::vector<Ship> ships;
	int ID;
	int ShipCount = 10;

private:

};

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

Map* Enemy::RandomizeShips()
{
	srand(time(NULL));

	int offset[] = { Game::Window().getSize().x / 2, Game::Window().getSize().y / 4 };
	Map* map = new Map(10, 10, offset);
	int shipToBuildIndex = 0;
	int shipsToBuild[] = { 5,4,4,3,3,3,2,2,2,2 };

	Origin origin;
	while (shipToBuildIndex < 10)
	{
		bool horizontal = (rand() % 10 + 1 > 5) ? true : false;
		origin.Y = rand() % 10;
		origin.X = rand() % 10;
		if (PlacingShip(shipsToBuild[shipToBuildIndex], horizontal, map, origin))
		{
			PlaceShip(shipsToBuild[shipToBuildIndex], horizontal, map, origin);
			shipToBuildIndex++;
		}
	}

	return map;
}