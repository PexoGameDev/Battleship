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


Map* RandomizeShips(Player* player)
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
			player->ships.push_back(PlaceShip(shipsToBuild[shipToBuildIndex], horizontal, map, origin));
			shipToBuildIndex++;
		}
	}

	return map;
}

int main()
{
	int shipToBuildIndex = 0;
	int shipsToBuild[] = { 5,4,4,3,3,3,2,2,2,2 };

	int offset[] = { Game::Window().getSize().x / 8, Game::Window().getSize().y / 4 };
	Map *playerMap = new Map(10, 10, offset);
	Game::Players = { Player("Hamsterius Hamstery", 0), Player("Squrriel Squire", 1) };

	//BETA TESTING SECTION
	bool SHOW_ENEMY_MAP = true;
	Map* enemyMap = RandomizeShips(&Game::Players[1]);

	int enemyOffset[] = { Game::Window().getSize().x / 2, Game::Window().getSize().y / 4 };
	Map *gameMap;
	if (SHOW_ENEMY_MAP)
		gameMap = new Map(10, 10, enemyOffset, MapFieldState::blank);
	else
		gameMap = new Map(10, 10, enemyOffset);
	//BETA TESTING SECTION

	sf::Font font;
	font.loadFromFile("C:/Windows/Fonts/Arial.ttf");

	bool placingHorizontal = true;
	int placingShipLenght = shipsToBuild[shipToBuildIndex];
	ShipPlacement sp = PlacingShip(placingShipLenght, placingHorizontal, playerMap);

	while (Game::Window().isOpen())
	{
		sf::Event event;
		while (Game::Window().pollEvent(event))
		{
			if(Game::State == GameState::PlayerSetUp)
				sp = PlacingShip(placingShipLenght, placingHorizontal, playerMap);

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

				case GameState::PlayerSetUp:
					sp = PlacingShip(placingShipLenght, placingHorizontal, playerMap);
					if (event.mouseButton.button == sf::Mouse::Right)
						placingHorizontal = !placingHorizontal;
					if (event.mouseButton.button == sf::Mouse::Left && sp.canPlace)
					{
						Game::Players[0].ships.push_back(PlaceShip(placingShipLenght, placingHorizontal, playerMap, sp.result));
						shipToBuildIndex++;
						if (shipToBuildIndex > 9)
							Game::State = GameState::PlayerTurn;
						else
							placingShipLenght = shipsToBuild[shipToBuildIndex];
					}
					break;

				case GameState::PlayerTurn:
					AimedShot shot = CanShoot(gameMap);
					if (event.mouseButton.button == sf::Mouse::Left && shot.canShoot)
					{
						Shoot(gameMap, enemyMap, shot.origin, &Game::Players[1]);
						Game::State = GameState::EnemyTurn;
					}
					break;

				case GameState::EnemyTurn:
					shot = CanShoot(playerMap);
					if (event.mouseButton.button == sf::Mouse::Left && shot.canShoot)
					{
						//Shoot(playerMap, shot.origin, &Game::Players[0]);
						Game::State = GameState::PlayerTurn;
					}
					break;

				}
				break;

			default:
				break;
			}
		}

		Game::Window().clear();

		playerMap->Draw();

		if(SHOW_ENEMY_MAP)
			enemyMap->Draw();

		gameMap->Draw();

		switch (Game::State)
		{
		default:
			break;

		case GameState::PlayerSetUp:
			PlacingShipDraw(placingShipLenght, placingHorizontal, playerMap, sp.result);
			break;

		case GameState::PlayerTurn:
			CanShoot(gameMap);
			break;
		}

		Game::Window().display();
	}

	return 0;
}
