#pragma once
#include "vector"

enum MapFieldState
{
	friendlyShip, hit, miss, empty
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

private:
	int coordinates[2];
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
	state = MapFieldState::empty;
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

