#include "PongGame.h"

PongGame::PongGame(int scoreToWin)
{
	m_playerOneScore = 0;
	m_playerTwoScore = 0;
	m_maxScore = scoreToWin;
	m_court = Court(sf::RectangleShape(sf::Vector2f(1400, 800)));
	m_ball = Ball(sf::Vector2f(700, 400), 10.0f);
	m_ball.SetVelocity(sf::Vector2f(2, 1));
	m_playerOne = Paddle(sf::RectangleShape(sf::Vector2f(20, 100)), sf::Vector2f(125, 400));
	m_playerTwo = Paddle(sf::RectangleShape(sf::Vector2f(20, 100)), sf::Vector2f(1325, 400));
	m_upperWall = sf::RectangleShape(sf::Vector2f(1400, 30));
	m_upperWall.setPosition(50, 50);
	m_lowerWall = sf::RectangleShape(sf::Vector2f(1400, 30));
	m_lowerWall.setPosition(50, 850);
	m_playState = SERVE_PLAYER_ONE;
}


PongGame::~PongGame()
{
}

void PongGame::PollKeys() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
		sf::Vector2f oldPos = m_playerOne.GetPosition();
		oldPos.y = std::max(std::min((oldPos.y - 3), 750.0f), 50.0f);
		m_playerOne.SetPosition(oldPos);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		sf::Vector2f oldPos = m_playerOne.GetPosition();
		oldPos.y = std::max(std::min((oldPos.y + 3), 750.0f), 50.0f);
		m_playerOne.SetPosition(oldPos);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
		sf::Vector2f oldPos = m_playerTwo.GetPosition();
		oldPos.y = std::max(std::min((oldPos.y - 3), 750.0f), 50.0f);
		m_playerTwo.SetPosition(oldPos);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
		sf::Vector2f oldPos = m_playerTwo.GetPosition();
		oldPos.y = std::max(std::min((oldPos.y + 3), 750.0f), 50.0f);
		m_playerTwo.SetPosition(oldPos);
	}
}

GAME_STATE PongGame::Update(float elapsedMilliseconds) {
	//ball movement
	m_ball.SetPosition(sf::Vector2f(m_ball.GetPosition().x + m_ball.GetVelocity().x, m_ball.GetPosition().y + m_ball.GetVelocity().y));
	//ball bounce
	sf::Vector2f bounceVect1 = CollisionHandler::DetectBallCollision(m_ball.GetBall(), m_ball.GetVelocity(), m_playerOne.GetSize(), m_playerOne.GetPosition(), true);
	//std::cout << "bounceVect.x: " << bounceVect1.x << "\n" << "bounceVect.y: " << bounceVect1.y << "\n";
	sf::Vector2f bounceVect2 = CollisionHandler::DetectBallCollision(m_ball.GetBall(), m_ball.GetVelocity(), m_playerTwo.GetSize(), m_playerTwo.GetPosition(), true);
	//std::cout << "bounceVect2.x: " << bounceVect2.x << "\n" << "bounceVect2.y: " << bounceVect2.y << "\n";
	sf::Vector2f bounceVect3 = CollisionHandler::DetectBallCollision(m_ball.GetBall(), m_ball.GetVelocity(), m_upperWall, m_upperWall.getPosition(), false);
	sf::Vector2f bounceVect4 = CollisionHandler::DetectBallCollision(m_ball.GetBall(), m_ball.GetVelocity(), m_lowerWall, m_lowerWall.getPosition(), false);


	if (bounceVect1 != sf::Vector2f(0.0f, 0.0f)) {
		std::cout << "BOUNCE \n";
		m_ball.SetVelocity(bounceVect1);
	}
	if (bounceVect2 != sf::Vector2f(0.0f, 0.0f)) {
		std::cout << "BOUNCE \n";
		m_ball.SetVelocity(bounceVect2);
	}
	if (bounceVect3 != sf::Vector2f(0.0f, 0.0f)) {
		std::cout << "BOUNCE \n";
		m_ball.SetVelocity(bounceVect3);
	}
	if (bounceVect4 != sf::Vector2f(0.0f, 0.0f)) {
		std::cout << "BOUNCE \n";
		m_ball.SetVelocity(bounceVect4);
	}

	return IN_GAME;
}

void PongGame::Render(float elapsedMilliseconds, sf::RenderWindow* window) {
	window->clear();
	//Draw order matters, will draw on top of last shape!
	window->draw(m_upperWall);
	window->draw(m_lowerWall);
	//window->draw(m_court.GetDimensions());
	window->draw(m_ball.GetBall());
	sf::RectangleShape renderPaddle1(m_playerOne.GetSize());
	renderPaddle1.setPosition(m_playerOne.GetPosition());
	sf::RectangleShape renderPaddle2(m_playerTwo.GetSize());
	renderPaddle2.setPosition(m_playerTwo.GetPosition());
	window->draw(renderPaddle1);
	window->draw(renderPaddle2);
	window->display();
}