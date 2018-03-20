#pragma once
#include "vector"
#include "MapField.h"
#include "SFML/Graphics.hpp"
#include "Game.h"
#include "Ship.h"

class Map
{
public:
	Map(int x, int y, MapFieldState defaultState = MapFieldState::empty);
	~Map();
	void Draw();
	
	std::vector<std::vector<MapField>> map;
private:
	int length_x;
	int length_y;
};

Map::Map(int x, int y, MapFieldState defaultState)
{
	length_x = x;
	length_y = y;

	for (int i = 0; i < x; i++)
	{
		map.push_back(std::vector<MapField>(0));
		for (int j = 0; j < y; j++)
		{
			sf::RectangleShape rectangle(sf::Vector2f(25, 25));
			map[i].push_back(MapField(i, j, rectangle));
			map[i][j].SetState(defaultState);
		}
	}
}

Map::~Map()
{
}

void Map::Draw()
{
	for (int i = 0; i < map.size(); i++)
		for (int j = 0; j < map[i].size(); j++)
		{
			switch (map[i][j].GetState())
			{
			default:
			case MapFieldState::blank:
				map[i][j].field.setFillColor(sf::Color(250, 250, 250,0));
				break;
			case MapFieldState::empty:
				map[i][j].field.setFillColor(sf::Color(250, 250, 250));
				break;
			case MapFieldState::friendlyShip:
				map[i][j].field.setFillColor(sf::Color(0, 127, 0));
				break;
			case MapFieldState::hit:
				map[i][j].field.setFillColor(sf::Color(127, 127, 0));
				break;
			case MapFieldState::miss:
				map[i][j].field.setFillColor(sf::Color(0, 0, 127));
				break;
			}

			map[i][j].field.setPosition(i*25.0 + i * 1.0 + Game::Window().getSize().x / 8, j*25.0 + j * 1.0 + Game::Window().getSize().y / 4);
			Game::Window().draw(map[i][j].field);
		}
}

Ship PlaceShip(int length, bool horizontal, Map *map)
{
	MapField origin;
	int originX = -1;
	int originY = -1;
	std::vector<MapField> shipsBody = {};

	for (int i = 0; i< map->map.size(); i++)
		for (int j = 0; j < map->map[i].size(); j++)
		{
			sf::RectangleShape field = map->map[i][j].field;
			sf::Vector2i mousePos = sf::Mouse::getPosition(Game::Window());
			if (field.getGlobalBounds().left <= mousePos.x &&
				field.getGlobalBounds().left + field.getGlobalBounds().width >= mousePos.x &&
				field.getGlobalBounds().top <= mousePos.y &&
				field.getGlobalBounds().top + field.getGlobalBounds().height >= mousePos.y)
			{
				origin = map->map[i][j];
				originX = i;
				originY = j;
			}
		}

	if (originX >= 0 && originY >= 0)
		if (horizontal)
		{
			int leftOffset = (length - 1) / 2;
			int rightOffset = length - leftOffset;
			int lastField = originX + rightOffset;
			for (int i = originX - leftOffset; i < lastField; i++)
			{
				map->map[i][originY].SetState(MapFieldState::friendlyShip);
				shipsBody.push_back(map->map[i][originY]);
			}
		}
		else
		{
			int upOffset = (length - 1) / 2;
			int downOffset = length - upOffset;
			int lastField = originY + downOffset;
			for (int i = originY - upOffset; i < lastField; i++)
			{
				map->map[originX][i].SetState(MapFieldState::friendlyShip);
				shipsBody.push_back(map->map[originX][i]);
			}
		}

	return Ship(shipsBody);
}

bool PlacingShip(int length, bool horizontal, Map *mainGameMap)
{
	Map *map = new Map(10, 10, MapFieldState::blank);
	MapField origin;
	int originX = -1;
	int originY = -1;
	bool canPlace = true;

	map->Draw();

	for (int i = 0; i< map->map.size(); i++)
		for (int j = 0; j < map->map[i].size(); j++)
		{
			sf::RectangleShape field = map->map[i][j].field;
			sf::Vector2i mousePos = sf::Mouse::getPosition(Game::Window());
			if (field.getGlobalBounds().left <= mousePos.x &&
				field.getGlobalBounds().left + field.getGlobalBounds().width >= mousePos.x &&
				field.getGlobalBounds().top <= mousePos.y &&
				field.getGlobalBounds().top + field.getGlobalBounds().height >= mousePos.y)
			{
				origin = map->map[i][j];
				originX = i;
				originY = j;
			}
		}

	if (originX >= 0 && originY >= 0)
		if (horizontal)
		{
			int leftOffset = (length - 1) / 2;
			int rightOffset = length - leftOffset;
			int lastField = originX + rightOffset;
			for (int i = originX - leftOffset; i < lastField; i++)
				if (i >= 0 && map->map.size() > i)
				{
					map->map[i][originY].SetState(MapFieldState::friendlyShip);
					if ((mainGameMap->map[i][originY].GetState() == MapFieldState::friendlyShip) ||
						(i - 1 >= 0 && mainGameMap->map[i - 1][originY].GetState() == MapFieldState::friendlyShip) ||
						(i + 1 <= 9 && mainGameMap->map[i + 1][originY].GetState() == MapFieldState::friendlyShip) ||
						(originY - 1 >= 0 && mainGameMap->map[i][originY - 1].GetState() == MapFieldState::friendlyShip) ||
						(originY + 1 <= 9 && mainGameMap->map[i][originY + 1].GetState() == MapFieldState::friendlyShip))
						canPlace = false;
				}
				else
					canPlace = false;
		}
		else
		{
			int upOffset = (length - 1) / 2;
			int downOffset = length - upOffset;
			int lastField = originY + downOffset;
			for (int i = originY - upOffset; i < lastField; i++)
				if (i >= 0 && map->map.size() > i)
				{
					map->map[originX][i].SetState(MapFieldState::friendlyShip);
					if ((mainGameMap->map[originX][i].GetState() == MapFieldState::friendlyShip) ||
						(originX - 1 >= 0 && mainGameMap->map[originX - 1][i].GetState() == MapFieldState::friendlyShip) ||
						(originX + 1 <= 9 && mainGameMap->map[originX + 1][i].GetState() == MapFieldState::friendlyShip) ||
						(i - 1 >= 0 && mainGameMap->map[originX][i - 1].GetState() == MapFieldState::friendlyShip) ||
						(i + 1 <= 9 && mainGameMap->map[originX][i + 1].GetState() == MapFieldState::friendlyShip))
						canPlace = false;
				}
				else
					canPlace = false;
		}
	map->Draw();
	return canPlace;
}
