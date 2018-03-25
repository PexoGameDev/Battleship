#pragma once
#include "Player.h"
#include "SFML/Graphics.hpp"
#include "Map.h"

enum GameState
{
	Paused, PlayerSetUp, PlayerTurn, EnemyTurn, GameOver
};

static class Game
{
public:
	
	Game();
	~Game();
	static sf::RenderWindow& Window();
	static std::vector<Player> Players;
	static GameState State;
	static void GameOver(Player player);
};

GameState Game::State = GameState::PlayerSetUp;
std::vector<Player> Game::Players = std::vector<Player>(0);

Game::Game(){}
Game::~Game(){}

void Game::GameOver(Player player)
{
	std::cout << "GAME OVER";

	sf::Font font;
	font.loadFromFile("C:/Windows/Fonts/Arial.ttf");
	sf::Text winner(player.Name,font);
	winner.setPosition(100, 100);
	winner.setStyle(sf::Text::Style::Bold);

	Game::State = GameState::GameOver;
}

sf::RenderWindow& Game::Window()
{
	static sf::RenderWindow window(sf::VideoMode(1024, 720), "Battleship", sf::Style::Default);;
	return window;
}

