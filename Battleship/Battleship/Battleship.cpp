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

}

void PlacingShip(int length, bool horizontal, Map *map)
{
	for (int i = 0; i< map->map.size(); i++)
		for (int j = 0; j < map->map[i].size(); j++)
		{
			sf::RectangleShape field = map->map[i][j].field;
			sf::Vector2i mousePos = sf::Mouse::getPosition(Game::Window());
			if (field.getGlobalBounds().left <= mousePos.x &&
				field.getGlobalBounds().left + field.getGlobalBounds().width >= mousePos.x &&
				field.getGlobalBounds().top <= mousePos.y &&
				field.getGlobalBounds().top + field.getGlobalBounds().height >= mousePos.y)
				map->map[i][j].SetState(MapFieldState::friendlyShip);
		}

	if (horizontal)
	{

	}
	else
	{

	}
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

		if (Game::GetGameState() == GameState::SetUp)
		{
			if (Game::Window().pollEvent(event) && event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					PlaceShip(placingShipLenght, placingHorizontal, map);
				}
				else
					placingHorizontal = !placingHorizontal;
			}
			PlacingShip(placingShipLenght, placingHorizontal, map);
		}

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
					if (event.mouseButton.button == sf::Mouse::Left)
						for(int i = 0; i< map->map.size();i++)
							for (int j = 0; j < map->map[i].size(); j++)
							{
								sf::RectangleShape field = map->map[i][j].field;
								sf::Vector2i mousePos = sf::Mouse::getPosition(Game::Window());
								if (field.getGlobalBounds().left <= mousePos.x &&
									field.getGlobalBounds().left + field.getGlobalBounds().width >= mousePos.x &&
									field.getGlobalBounds().top <= mousePos.y &&
									field.getGlobalBounds().top + field.getGlobalBounds().height >= mousePos.y)
									map->map[i][j].SetState(MapFieldState::friendlyShip);
							}
					break;
				}
				break;

			default:
				break;
			}
		}

		Game::Window().clear();
		map->Draw(Game::Window(), font);
		Game::Window().display();
	}

	return 0;
}
