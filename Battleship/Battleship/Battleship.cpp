#include "stdafx.h"
#include "iostream"
#include "vector"
#include "string"
#include "SFML/Graphics.hpp"
#include "MapField.h"
#include "Map.h"
#include "Game.h"
#include "Player.h"
#include "Ship.h"



void PlaceShip(int length, bool horizontal, Map *map)
{
	MapField origin;
	int originX = -1;
	int originY = -1;
	
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
				map->map[i][originY].SetState(MapFieldState::friendlyShip);
		}
		else
		{
			int upOffset = (length - 1) / 2;
			int downOffset = length - upOffset;
			int lastField = originY + downOffset;
			for (int i = originY - upOffset; i < lastField; i++)
				map->map[originX][i].SetState(MapFieldState::friendlyShip);
		}

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

	if(originX>=0 && originY>=0)
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

void StartGame()
{
	std::vector<Player> players = { Player("Hamsterius Hamstery",3), Player("Squrriel Squire",3) };
	Game mainGame(players);
	Game::SetGameState(GameState::SetUp);

	std::vector<Ship> shipsToBuild = {};
}

int main()
{
	Map *map = new Map(10, 10);
	StartGame();

	sf::Font font;
	font.loadFromFile("C:/Windows/Fonts/Arial.ttf");

	bool placingHorizontal = true;
	int placingShipLenght = 5;
	while (Game::Window().isOpen())
	{
		sf::Event event;
		while (Game::Window().pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				Game::Window().close();
				break;

			case sf::Event::KeyPressed:
				break;

			case sf::Event::MouseButtonPressed:
				switch (Game::GetGameState())
				{
				default:
					break;
				case GameState::SetUp:
					if (event.mouseButton.button == sf::Mouse::Right)
						placingHorizontal = !placingHorizontal;
					if (event.mouseButton.button == sf::Mouse::Left && PlacingShip(placingShipLenght, placingHorizontal, map))
						PlaceShip(placingShipLenght, placingHorizontal, map);
					break;
				}
				break;

			default:
				break;
			}
		}

		//RENDERING SECTION
		Game::Window().clear();
		map->Draw();
		if (Game::GetGameState() == GameState::SetUp)
			PlacingShip(placingShipLenght, placingHorizontal, map);
		Game::Window().display();
	}

	return 0;
}
