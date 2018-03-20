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

int shipToBuildIndex = 0;
std::vector<int> shipsToBuild = {5,4,4,3,3,3,2,2,2,2};

void StartGame()
{
	Game::Players = { Player("Hamsterius Hamstery"), Player("Squrriel Squire") };
}

int main()
{
	Map *map = new Map(10, 10);
	StartGame();

	sf::Font font;
	font.loadFromFile("C:/Windows/Fonts/Arial.ttf");

	bool placingHorizontal = true;
	int placingShipLenght = shipsToBuild[shipToBuildIndex];
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
				switch (Game::State)
				{
				default:
					break;
				case GameState::SetUp:
					if (event.mouseButton.button == sf::Mouse::Right)
						placingHorizontal = !placingHorizontal;
					if (event.mouseButton.button == sf::Mouse::Left && PlacingShip(placingShipLenght, placingHorizontal, map))
					{
						Game::Players[0].ships.push_back(PlaceShip(placingShipLenght, placingHorizontal, map));
						shipToBuildIndex++;
						if (shipToBuildIndex >= 10)
							Game::State = GameState::PlayerTurn; // START GAME
						else
							placingShipLenght = shipsToBuild[shipToBuildIndex];
					}
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
		if (Game::State == GameState::SetUp)
			PlacingShip(placingShipLenght, placingHorizontal, map);
		Game::Window().display();
	}

	return 0;
}
