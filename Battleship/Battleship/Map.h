#pragma once
#include "vector"
#include "MapField.h"
#include "SFML/Graphics.hpp"
#include "Game.h"
#include "Ship.h"
#include "vector"

class Map
{
public:
	Map(int x, int y, int thisMapOffset[], MapFieldState defaultState = MapFieldState::empty);
	~Map();
	void Draw();
	void SetOffset(int offset[]);
	void SetAllFields(MapFieldState state);
	std::vector<std::vector<MapField*>> map;
	int mapOffset[2] = { 0,0 };
private:
	int length_x;
	int length_y;
};

Map::Map(int x, int y, int thisMapOffset[], MapFieldState defaultState)
{
	length_x = x;
	length_y = y;

	for (int i = 0; i < x; i++)
	{
		map.push_back(std::vector<MapField*>(0));
		for (int j = 0; j < y; j++)
		{
			sf::RectangleShape rectangle(sf::Vector2f(25, 25));
			map[i].push_back(new MapField(i, j, rectangle));
			map[i][j]->SetState(defaultState);
			map[i][j]->field.setPosition(i*25.0 + i * 1.0 + thisMapOffset[0], j*25.0 + j * 1.0 + thisMapOffset[1]);
		}
	}
	mapOffset[0] = thisMapOffset[0];
	mapOffset[1] = thisMapOffset[1];
}

Map::~Map()
{
}

void Map::SetOffset(int offset[])
{
	for (int x = 0; x < 10; x++)
		for (int y = 0; y < 10; y++)
			map[x][y]->field.setPosition(x * 25.0 + x * 1.0 + offset[0], y*25.0 + y * 1.0 + offset[1]);
}

void Map::SetAllFields(MapFieldState state)
{
	for (int x = 0; x < 10; x++)
		for (int y = 0; y < 10; y++)
			map[x][y]->SetState(state);
}

void Map::Draw()
{
	for (int i = 0; i < map.size(); i++)
		for (int j = 0; j < map[i].size(); j++)
		{
			switch (map[i][j]->GetState())
			{
			default:
			case MapFieldState::blank:
				map[i][j]->field.setFillColor(sf::Color(250, 250, 250, 0));
				break;
			case MapFieldState::empty:
				map[i][j]->field.setFillColor(sf::Color(250, 250, 250));
				break;
			case MapFieldState::friendlyShip:
				map[i][j]->field.setFillColor(sf::Color(0, 127, 0));
				break;
			case MapFieldState::hit:
				map[i][j]->field.setFillColor(sf::Color(250, 0, 0));
				break;
			case MapFieldState::miss:
				map[i][j]->field.setFillColor(sf::Color(0, 0, 127));
				break;
			case MapFieldState::aim:
				map[i][j]->field.setFillColor(sf::Color(127, 127, 127));
				break;
			case MapFieldState::sunk:
				map[i][j]->field.setFillColor(sf::Color(127, 64, 0));
				break;
			}

			Game::Window().draw(map[i][j]->field);
		}
}

struct Origin
{
	int X;
	int Y;
};

struct ShipPlacement
{
	Origin result;
	bool canPlace;
};

struct AimedShot
{
	Origin origin;
	bool canShoot;
};

Origin GetFieldUnderPointer(Map *map)
{
	Origin result;
	result.X = -1;
	result.Y = -1;

	for (int i = 0; i< map->map.size(); i++)
		for (int j = 0; j < map->map[i].size(); j++)
		{
			sf::RectangleShape field = map->map[i][j]->field;
			sf::Vector2i mousePos = sf::Mouse::getPosition(Game::Window());
			if (field.getGlobalBounds().left <= mousePos.x &&
				field.getGlobalBounds().left + field.getGlobalBounds().width >= mousePos.x &&
				field.getGlobalBounds().top <= mousePos.y &&
				field.getGlobalBounds().top + field.getGlobalBounds().height >= mousePos.y)
			{
				result.X = i;
				result.Y = j;
			}
		}
	return result;
}

Ship PlaceShip(int length, bool horizontal, Map *map, Origin origin)
{
	std::vector<MapField*> shipsBody = {};

	if (origin.X >= 0 && origin.Y >= 0)
		if (horizontal)
		{
			int leftOffset = (length - 1) / 2;
			int rightOffset = length - leftOffset;
			int lastField = origin.X + rightOffset;
			for (int i = origin.X - leftOffset; i < lastField; i++)
			{
				map->map[i][origin.Y]->SetState(MapFieldState::friendlyShip);
				shipsBody.push_back(map->map[i][origin.Y]);
			}
		}
		else
		{
			int upOffset = (length - 1) / 2;
			int downOffset = length - upOffset;
			int lastField = origin.Y + downOffset;
			for (int i = origin.Y - upOffset; i < lastField; i++)
			{
				map->map[origin.X][i]->SetState(MapFieldState::friendlyShip);
				shipsBody.push_back(map->map[origin.X][i]);
			}
		}
	return Ship(shipsBody, length);
}

ShipPlacement PlacingShip(int length, bool horizontal, Map *mainGameMap)
{
	Origin origin = GetFieldUnderPointer(mainGameMap);
	bool canPlace = true;

	if (origin.X >= 0 && origin.Y >= 0)
		if (horizontal)
		{
			int leftOffset = (length - 1) / 2;
			int rightOffset = length - leftOffset;
			int lastField = origin.X + rightOffset;
			for (int i = origin.X - leftOffset; i < lastField; i++)
				if (i >= 0 && mainGameMap->map.size() > i)
				{
					if ((mainGameMap->map[i][origin.Y]->GetState() == MapFieldState::friendlyShip) ||
						(i - 1 >= 0 && mainGameMap->map[i - 1][origin.Y]->GetState() == MapFieldState::friendlyShip) ||
						(i + 1 <= 9 && mainGameMap->map[i + 1][origin.Y]->GetState() == MapFieldState::friendlyShip) ||
						(origin.Y - 1 >= 0 && mainGameMap->map[i][origin.Y - 1]->GetState() == MapFieldState::friendlyShip) ||
						(origin.Y + 1 <= 9 && mainGameMap->map[i][origin.Y + 1]->GetState() == MapFieldState::friendlyShip))
						canPlace = false;
				}
				else
					canPlace = false;
		}
		else
		{
			int upOffset = (length - 1) / 2;
			int downOffset = length - upOffset;
			int lastField = origin.Y + downOffset;
			for (int i = origin.Y - upOffset; i < lastField; i++)
				if (i >= 0 && mainGameMap->map.size() > i)
				{
					if ((mainGameMap->map[origin.X][i]->GetState() == MapFieldState::friendlyShip) ||
						(origin.X - 1 >= 0 && mainGameMap->map[origin.X - 1][i]->GetState() == MapFieldState::friendlyShip) ||
						(origin.X + 1 <= 9 && mainGameMap->map[origin.X + 1][i]->GetState() == MapFieldState::friendlyShip) ||
						(i - 1 >= 0 && mainGameMap->map[origin.X][i - 1]->GetState() == MapFieldState::friendlyShip) ||
						(i + 1 <= 9 && mainGameMap->map[origin.X][i + 1]->GetState() == MapFieldState::friendlyShip))
						canPlace = false;
				}
				else
					canPlace = false;
		}
	else
		canPlace = false;
	return ShipPlacement{ origin, canPlace };
}

int mapOffset[2] = { 0,0 };
Map *map = new Map(10, 10, mapOffset, MapFieldState::blank);

void PlacingShipDraw(int length, bool horizontal, Map *mainGameMap, Origin origin)
{
	if(map->mapOffset != mainGameMap->mapOffset)
		map->SetOffset(mainGameMap->mapOffset);

	if (origin.X >= 0 && origin.Y >= 0)
		if (horizontal)
		{
			int leftOffset = (length - 1) / 2;
			int rightOffset = length - leftOffset;
			int lastField = origin.X + rightOffset;
			for (int i = origin.X - leftOffset; i < lastField; i++)
				if (i >= 0 && map->map.size() > i)
					map->map[i][origin.Y]->SetState(MapFieldState::friendlyShip);
		}
		else
		{
			int upOffset = (length - 1) / 2;
			int downOffset = length - upOffset;
			int lastField = origin.Y + downOffset;
			for (int i = origin.Y - upOffset; i < lastField; i++)
				if (i >= 0 && map->map.size() > i)
					map->map[origin.X][i]->SetState(MapFieldState::friendlyShip);
		}
	map->Draw();
	map->SetAllFields(MapFieldState::blank);
}

AimedShot CanShoot(Map *mainGameMap)
{
	if (map->mapOffset != mainGameMap->mapOffset)
		map->SetOffset(mainGameMap->mapOffset);

	Origin origin = GetFieldUnderPointer(mainGameMap);
	bool result = false;
	if (origin.X >= 0 && origin.Y >= 0)
	{
		if (mainGameMap->map[origin.X][origin.Y]->GetState() != MapFieldState::miss && mainGameMap->map[origin.X][origin.Y]->GetState() != MapFieldState::hit && mainGameMap->map[origin.X][origin.Y]->GetState() != MapFieldState::sunk)
		{
			map->map[origin.X][origin.Y]->SetState(MapFieldState::aim);
			result = true;
		}
	}
	map->Draw();
	map->SetAllFields(MapFieldState::blank);
	return AimedShot{ origin,result };
}

void Shoot(Map *mainGameMap, Origin origin, Player* targetPlayer)
{
	if (origin.X >= 0 && origin.Y >= 0)
		if (mainGameMap->map[origin.X][origin.Y]->GetState() == MapFieldState::friendlyShip)
		{
			mainGameMap->map[origin.X][origin.Y]->SetState(MapFieldState::hit);
			for (int i = 0; i < targetPlayer->ships.size(); i++)
			{
				for (int j = 0; j < targetPlayer->ships[i].HP; j++)
				{
					if (mainGameMap->map[origin.X][origin.Y]->coordinates[0] == targetPlayer->ships[i].body[j]->coordinates[0]
						&& mainGameMap->map[origin.X][origin.Y]->coordinates[1] == targetPlayer->ships[i].body[j]->coordinates[1])
					{
						targetPlayer->ships[i].Hit();
						//std::cout << "Ship hit - HP left: "<< targetPlayer->ships[i].HP<<"\n";
						if (targetPlayer->ships[i].HP <= 0)
						{
							//std::cout << "Ship sunk \n";
							targetPlayer->ShipCount--;
							if (targetPlayer->ShipCount <= 0)
								Game::GameOver(Game::Players[(targetPlayer->ID + 1) % 2]);
						}
					}
				}
			}
		}
		else
			mainGameMap->map[origin.X][origin.Y]->SetState(MapFieldState::miss);
	/*
	for (int i = 0; i < Game::Players[0].ships.size(); i++)
	{
		std::cout << "Player 1 ship hp:" << Game::Players[0].ships[i].HP << "\n";
	}

	for (int i = 0; i < Game::Players[1].ships.size(); i++)
	{
		std::cout << "Player 2 ship hp:" << Game::Players[1].ships[i].HP << "\n";
	}*/
}
