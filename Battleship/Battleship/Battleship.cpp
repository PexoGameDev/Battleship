#include "stdafx.h"
#include "iostream"
#include "vector"
#include "SFML/Graphics.hpp"
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
	unsigned int length_x;
	unsigned int length_y;
	std::vector<std::vector<bool>> map;

	Map(unsigned int x, unsigned int y)
	{
		length_x = x;
		length_y = y;

		for (int i = 0; i < x; i++)
		{
			map.push_back(std::vector<bool>(y));
			for (int j = 0; j<y; j++)
				map[i].push_back(false);
		}
	}
private:
};

int main()
{
	Map *map = new Map(3, 10);
	Ship *firstShip = new Ship(400, 300, -1, 3);

	sf::RenderWindow window(sf::VideoMode(800, 600),
		"Battleship", sf::Style::Default);

	sf::Font font;
	font.loadFromFile("C:/Windows/Fonts/Arial.ttf");

	sf::Text text;
	text.setFont(font);
	text.setPosition(0, 0);
	text.setString("Welcome! Let the championships begin!");

	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		window.draw(text);
		firstShip->Draw(window);
		window.display();
	}

    return 0;
}
