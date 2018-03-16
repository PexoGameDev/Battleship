#pragma once
#include "Player.h"

enum GameState
{
	Paused, SetUp, PlayerTurn, EnemyTurn, GameOver
};

static class Game
{
public:
	
	Game(std::vector<Player> newPlayers);
	~Game();
	static void SetGameState(GameState newState);
	static GameState GetGameState();

private:
	static GameState state;
	static std::vector<Player> players;
};

GameState Game::state = GameState::SetUp;

Game::Game(std::vector<Player> newPlayers)
{
	static GameState state = GameState::SetUp;
	static std::vector<Player> players = newPlayers;
}

Game::~Game()
{
}


void Game::SetGameState(GameState newState)
{
	Game::state = newState;
}

GameState Game::GetGameState()
{
	return Game::state;
}
