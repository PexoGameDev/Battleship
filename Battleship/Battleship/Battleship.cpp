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
