#pragma once
enum GameState
{
	Paused, SetUp, PlayerTurn, EnemyTurn, GameOver
};

static class Game
{
public:
	
	Game();
	~Game();
	static void SetGameState(GameState newState);
	static GameState GetGameState();

private:
	static GameState state;
};

Game::Game()
{
	static GameState state = GameState::SetUp;
}

Game::~Game()
{
}

GameState Game::state = GameState::SetUp;

void Game::SetGameState(GameState newState)
{
	Game::state = newState;
}

GameState Game::GetGameState()
{
	return Game::state;
}
