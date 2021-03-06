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
#include "random"
#include "cstdlib"
#include "time.h"

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

void RandomShoot(Map* targetMap, Player* targetPlayer)
{
	Origin target;
	target.Y = rand() % 10;
	target.X = rand() % 10;

	while (targetMap->map[target.X][target.Y]->GetState() == MapFieldState::miss ||
		targetMap->map[target.X][target.Y]->GetState() == MapFieldState::hit ||
		targetMap->map[target.X][target.Y]->GetState() == MapFieldState::sunk)
	{
		target.Y = rand() % 10;
		target.X = rand() % 10;
	}

	if (targetMap->map[target.X][target.Y]->GetState() == MapFieldState::friendlyShip)
	{
		targetMap->map[target.X][target.Y]->SetState(MapFieldState::hit);

		for (int i = 0; i < targetPlayer->ships.size(); i++)
			for (int j = 0; j < targetPlayer->ships[i].body.size(); j++)
				if (targetMap->map[target.X][target.Y]->coordinates[0] == targetPlayer->ships[i].body[j]->coordinates[0]
					&& targetMap->map[target.X][target.Y]->coordinates[1] == targetPlayer->ships[i].body[j]->coordinates[1])
				{
					targetPlayer->ships[i].Hit();
					if (targetPlayer->ships[i].HP <= 0)
					{
						for (int x = 0; x < targetPlayer->ships[i].body.size(); x++)
							targetMap->map[targetPlayer->ships[i].body[x]->coordinates[0]][targetPlayer->ships[i].body[x]->coordinates[1]]->SetState(MapFieldState::sunk);
						targetPlayer->ShipCount--;
						if (targetPlayer->ShipCount <= 0)
							Game::GameOver(Game::Players[(targetPlayer->ID + 1) % 2]);
					}
					return;
				}
	}
	else
		targetMap->map[target.X][target.Y]->SetState(MapFieldState::miss);
}

int main()
{
	int shipToBuildIndex = 0;
	int shipsToBuild[] = { 5,4,4,3,3,3,2,2,2,2 };

	int offset[] = { Game::Window().getSize().x / 8, Game::Window().getSize().y / 4 };
	Map *playerMap = new Map(10, 10, offset);
	Game::Players = { Player("Hamsterius Hamstery", 0), Player("Squrriel Squire", 1) };

	//BETA TESTING SECTION
	bool SHOW_ENEMY_MAP = false;
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
			if (Game::State == GameState::EnemyTurn)
			{
				RandomShoot(playerMap, &Game::Players[0]);
				Game::State = GameState::PlayerTurn;
			}

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
