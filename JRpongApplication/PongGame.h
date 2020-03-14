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
	sf::RectangleShape m_p1_goal;
	sf::RectangleShape m_p2_goal;
	sf::Font m_font;
	sf::Text m_p1_score;
	sf::Text m_p2_score;

	PLAY_STATE m_playState;

	GAME_STATE ScoreP1();

	GAME_STATE ScoreP2();

	GAME_STATE UpdateTowardP1();

	GAME_STATE UpdateTowardP2();

	GAME_STATE ServeP1();
	
	GAME_STATE ServeP2();

public:
	PongGame(int scoreToWin);
	~PongGame();

	GAME_STATE Update(float elapsedMilliseconds);

	void PollKeys();


	void Render(float elapsedMilliseconds, sf::RenderWindow* window);
};

