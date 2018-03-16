#pragma once
class Ship
{
private:
	unsigned int position_x;
	unsigned int position_y;
	int shipLength;
	int shipDirection;

public:
	Ship(unsigned int x, unsigned int y, int direction, unsigned int length);
	~Ship();
	void Draw(sf::RenderWindow &window);
};

Ship::Ship(unsigned int x, unsigned int y, int direction, unsigned int length)
{
	Ship::position_x = x;
	Ship::position_y = y;
	Ship::shipDirection = direction;
	Ship::shipLength = length;
}

Ship::~Ship()
{
}
void Ship::Draw(sf::RenderWindow &window)
{
	sf::RectangleShape rectangle(sf::Vector2f(25 * shipLength * shipDirection, 25));
	rectangle.setFillColor(sf::Color(255, 50, 50));
	rectangle.setPosition(position_x, position_y);
	window.draw(rectangle);
}