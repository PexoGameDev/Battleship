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
int main()
{
	std::vector<Player> players = { Player("Hamsterius Hamstery",3), Player("Squrriel Squire",3) };
	Game mainGame(players);
	Game::SetGameState(GameState::SetUp);

	Map *map = new Map(10, 10);

	sf::RenderWindow window(sf::VideoMode(1024, 720),
		"Battleship", sf::Style::Default);

	sf::Font font;
	font.loadFromFile("C:/Windows/Fonts/Arial.ttf");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
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
								sf::Vector2i mousePos = sf::Mouse::getPosition(window);
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

		window.clear();
		map->Draw(window, font);
		window.display();
	}

	return 0;
}

void PlaceShip(std::vector<MapField> fields)
{

}