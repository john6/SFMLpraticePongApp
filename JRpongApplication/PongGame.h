#pragma once
#include "Court.h"
#include "Ball.h"
#include "Paddle.h"
#include "CollisionHandler.h"
#include "GAME_STATE.h"
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <iostream>

enum PLAY_STATE { SERVE_PLAYER_ONE, SERVE_PLAYER_TWO, TOWARD_PLAYER_ONE, TOWARD_PLAYER_TWO };

class PongGame
{
private:
	int m_playerOneScore;
	int	m_playerTwoScore;
	int	m_maxScore;
	Court m_court;
	Ball m_ball;
	Paddle m_playerOne;
	Paddle m_playerTwo;
	sf::RectangleShape m_upperWall;
	sf::RectangleShape m_lowerWall;
	PLAY_STATE m_playState;

public:
	PongGame(int scoreToWin);
	~PongGame();
	
	GAME_STATE Update(float elapsedMilliseconds);

	void PollKeys();


	void Render(float elapsedMilliseconds, sf::RenderWindow* window);
};

