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
#include "Enemy.h"

int main()
{
	int shipToBuildIndex = 0;
	int shipsToBuild[] = { 5,4,4,3,3,3,2,2,2,2 };

	int offset[] = { Game::Window().getSize().x / 8, Game::Window().getSize().y / 4 };
	Map *playerMap = new Map(10, 10, offset);
	int enemyOffset[] = { Game::Window().getSize().x / 2, Game::Window().getSize().y / 4 };
	Map *gameMap = new Map(10, 10, enemyOffset);
	Game::Players = { Player("Hamsterius Hamstery", 0), Player("Squrriel Squire", 1) };

	//BETA TESTING SECTION
	bool SHOW_ENEMY_MAP = false;
	Enemy enemy;
	Map* enemyMap = enemy.RandomizeShips();
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
						{
							shipToBuildIndex = 0;
							Game::State = GameState::EnemySetUp;
						}
						placingShipLenght = shipsToBuild[shipToBuildIndex];
					}
					break;

				case GameState::PlayerTurn:
					AimedShot shot = CanShoot(enemyMap);
					if (event.mouseButton.button == sf::Mouse::Left && shot.canShoot)
					{
						Shoot(enemyMap, shot.origin, &Game::Players[1]);
						Game::State = GameState::EnemyTurn;
					}
					break;

				case GameState::EnemyTurn:
					shot = CanShoot(playerMap);
					if (event.mouseButton.button == sf::Mouse::Left && shot.canShoot)
					{
						Shoot(playerMap, shot.origin, &Game::Players[0]);
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
		if (SHOW_ENEMY_MAP)
			enemyMap->Draw();
		else
			gameMap->Draw();

		switch (Game::State)
		{
		default:
			break;

		case GameState::PlayerSetUp:
			PlacingShipDraw(placingShipLenght, placingHorizontal, playerMap, sp.result);
			break;

		case GameState::PlayerTurn:
			CanShoot(enemyMap);
			break;
		}

		Game::Window().display();
	}

	return 0;
}
