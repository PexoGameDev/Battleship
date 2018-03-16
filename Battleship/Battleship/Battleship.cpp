#include "stdafx.h"
#include "iostream"
#include "vector"
#include "SFML/Graphics.hpp"
#include "Game.h"

class Ship
{
public:
	unsigned int position_x;
	unsigned int position_y;
	int shipLength;
	int shipDirection;

	Ship(unsigned int x, unsigned int y, int direction, unsigned int length)
	{
		position_x = x;
		position_y = y;
		shipDirection = direction;
		shipLength = length;
	}

	void Draw(sf::RenderWindow &window)
	{
		sf::RectangleShape rectangle(sf::Vector2f(25 * shipLength * shipDirection, 25));
		rectangle.setFillColor(sf::Color(255, 50, 50));
		rectangle.setPosition(position_x, position_y);
		window.draw(rectangle);
	}
private:

};

class Map
{
public:
	enum MapState
	{
		friendlyShip, enemyShip, hit, miss, empty
	};
	int length_x;
	int length_y;
	std::vector<std::vector<MapState>> map;

	Map(int x, int y)
	{
		length_x = x;
		length_y = y;

		for (int i = 0; i < x; i++)
		{
			map.push_back(std::vector<MapState>(0));
			for (int j = 0; j<y; j++)
				map[i].push_back(MapState::empty);
		}
	}

	void Draw(sf::RenderWindow &window, sf::Font &font)
	{
		for (int i = 0; i < map.size(); i++)
			for (int j = 0; j < map[i].size(); j++)
			{
				sf::RectangleShape rectangle(sf::Vector2f(25, 25));

				switch (map[i][j])
				{
				default:
				case MapState::empty:
					rectangle.setFillColor(sf::Color(250, 250, 250));
					break;
				case MapState::friendlyShip:
					rectangle.setFillColor(sf::Color(0, 127, 0));
					break;
				case MapState::enemyShip:
					rectangle.setFillColor(sf::Color(127, 0, 0));
					break;
				case MapState::hit:
					rectangle.setFillColor(sf::Color(127, 127, 0));
					break;
				case MapState::miss:
					rectangle.setFillColor(sf::Color(0, 0, 127));
					break;
				}

				rectangle.setPosition(i*25.0 + i * 1.0 + window.getSize().x / 8, j*25.0 + j * 1.0 + window.getSize().y / 4);
				window.draw(rectangle);
			}
		sf::Text text("Your Map", font);
		text.setStyle(sf::Text::Underlined);
		text.setPosition(window.getSize().x / 8, window.getSize().y / 4 - 50);
		window.draw(text);

		if (Game::GetGameState() == GameState::SetUp)
		{
			sf::Text shipsLeft("Ships Left\n", font);
			shipsLeft.setStyle(sf::Text::Italic);
			shipsLeft.setScale(0.6, 0.6);
			shipsLeft.setPosition(window.getSize().x / 8 + 30 * length_x, window.getSize().y / 4 - 50);
			window.draw(shipsLeft);
		}
	}
private:
};

int main()
{
	Game::SetGameState(GameState::SetUp);

	Map *map = new Map(10, 10);
	Ship *firstShip = new Ship(400, 300, -1, 3);

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
		firstShip->Draw(window);
		map->Draw(window, font);

		window.display();
	}

    return 0;
}
