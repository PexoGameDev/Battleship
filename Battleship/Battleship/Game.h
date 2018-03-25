#pragma once
#include "Player.h"
#include "SFML/Graphics.hpp"
#include "Map.h"

enum GameState
{
	Paused, PlayerSetUp, PlayerTurn, EnemyTurn, GameOver, EnemySetUp
};

static class Game
{
public:
	
	Game();
	~Game();
	static sf::RenderWindow& Window();
	static std::vector<Player> Players;
	static GameState State;
};

GameState Game::State = GameState::PlayerSetUp;
std::vector<Player> Game::Players = std::vector<Player>(0);

Game::Game()
{
}

Game::~Game()
{
}

sf::RenderWindow& Game::Window()
{
	static sf::RenderWindow window(sf::VideoMode(1024, 720), "Battleship", sf::Style::Default);;
	return window;
}
