#pragma once
#include "vector"
#include "MapField.h"
#include "SFML/Graphics.hpp"
#include "Game.h"

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
