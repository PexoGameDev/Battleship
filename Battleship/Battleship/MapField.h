#pragma once
#include "vector"

enum MapFieldState
{
	friendlyShip, hit, miss, empty, blank, aim, sunk
};

class MapField
{
public:
	MapField(int x, int y, sf::RectangleShape square);
	MapField();
	~MapField();
	void Draw();
	void SetState(MapFieldState newState);
	MapFieldState GetState();

	sf::RectangleShape field;
	int coordinates[2];

private:
	MapFieldState state;
};

MapField::MapField()
{
}

MapField::MapField(int x, int y, sf::RectangleShape square)
{
	coordinates[0] = x;
	coordinates[1] = y;
	field = square;
}

MapField::~MapField()
{
}

void MapField::SetState(MapFieldState newState)
{
	state = newState;
}

MapFieldState MapField::GetState()
{
	return state;
}

void MapField::Draw()
{

}

