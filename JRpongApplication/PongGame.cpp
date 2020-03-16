#include "PongGame.h"

PongGame::PongGame(int scoreToWin)
{
	m_playerOneScore = 0;
	m_playerTwoScore = 0;
	m_maxScore = scoreToWin;
	m_court = Court(sf::RectangleShape(sf::Vector2f(1400, 800)));
	m_ball = Ball(sf::Vector2f(700, 400), 10.0f);
	m_ball.SetVelocity(sf::Vector2f(15, 5));
	m_playerOne = Paddle(sf::RectangleShape(sf::Vector2f(20, 100)), sf::Vector2f(125, 400));
	m_playerTwo = Paddle(sf::RectangleShape(sf::Vector2f(20, 100)), sf::Vector2f(1350, 400));
	m_upperWall = sf::RectangleShape(sf::Vector2f(1400, 15));
	m_upperWall.setPosition(50, 50);
	m_lowerWall = sf::RectangleShape(sf::Vector2f(1400, 15));
	m_lowerWall.setPosition(50, 850);
	m_p1_goal = sf::RectangleShape(sf::Vector2f(50, 785));
	m_p1_goal.setPosition(1400, 65);
	m_p1_goal.setFillColor(sf::Color::Black);
	m_p2_goal = sf::RectangleShape(sf::Vector2f(50, 785));
	m_p2_goal.setPosition(sf::Vector2f(50, 65));
	m_p2_goal.setFillColor(sf::Color::Black);
	m_playState = SERVE_PLAYER_ONE;
	m_p1_score = sf::Text();
	if (!m_font.loadFromFile("kongtext.ttf")) {
		std::cout << "fuck";
	}
	m_p1_score.setFont(m_font);
	m_p1_score.setString(std::to_string(0));
	m_p1_score.setCharacterSize(40);
	m_p1_score.setFillColor(sf::Color::White);
	m_p1_score.setPosition(sf::Vector2f(120.0f, 0.0f));

	m_p2_score.setFont(m_font);
	m_p2_score.setString(std::to_string(0));
	m_p2_score.setCharacterSize(40);
	m_p2_score.setFillColor(sf::Color::White);
	m_p2_score.setPosition(sf::Vector2f(1335.0f, 0.0f));
}

PongGame::~PongGame()
{
}

void PongGame::PollKeys() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
		sf::Vector2f oldPos = m_playerOne.GetPosition();
		oldPos.y = std::max(std::min((oldPos.y - 15), 750.0f), 50.0f);
		m_playerOne.SetPosition(oldPos);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		sf::Vector2f oldPos = m_playerOne.GetPosition();
		oldPos.y = std::max(std::min((oldPos.y + 15), 750.0f), 50.0f);
		m_playerOne.SetPosition(oldPos);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
		sf::Vector2f oldPos = m_playerTwo.GetPosition();
		oldPos.y = std::max(std::min((oldPos.y - 15), 750.0f), 50.0f);
		m_playerTwo.SetPosition(oldPos);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
		sf::Vector2f oldPos = m_playerTwo.GetPosition();
		oldPos.y = std::max(std::min((oldPos.y + 15), 750.0f), 50.0f);
		m_playerTwo.SetPosition(oldPos);
	}
}

GAME_STATE PongGame::ScoreP1() {
	m_ball.~Ball();
	m_playerOneScore += 1;
	m_p1_score.setString(std::to_string(m_playerOneScore));
	if (m_playerOneScore >= m_maxScore) {
		m_playState = SERVE_PLAYER_TWO;
		return MENU;
	}
	m_playState = SERVE_PLAYER_TWO;
	return IN_GAME;
}

GAME_STATE PongGame::ScoreP2() {
	m_ball.~Ball();
	m_playerTwoScore += 1;
	m_p2_score.setString(std::to_string(m_playerTwoScore));
	if (m_playerTwoScore >= m_maxScore) {
		m_playState = SERVE_PLAYER_ONE;
		return MENU;
	}
	m_playState = SERVE_PLAYER_ONE;
	return IN_GAME;
}

GAME_STATE PongGame::ServeP1() {
	m_ball = Ball(sf::Vector2f(m_playerOne.GetPosition().x + 25, m_playerOne.GetPosition().y + (m_playerOne.GetSize().getSize().y / 2)), 10.0f);
	m_ball.SetVelocity(sf::Vector2f(0, 0));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		float randomNum = (float) (rand() % 10);
		randomNum = (randomNum - 5.0f);
		std::cout << randomNum << "\n";
		m_ball.SetVelocity(sf::Vector2f(15, randomNum));
		m_playState = TOWARD_PLAYER_TWO;
	}
	return IN_GAME;
}

GAME_STATE PongGame::ServeP2() {
	m_ball = Ball(sf::Vector2f(m_playerTwo.GetPosition().x - 25, m_playerTwo.GetPosition().y + (m_playerTwo.GetSize().getSize().y / 2)), 10.0f);
	m_ball.SetVelocity(sf::Vector2f(0, 0));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
		float randomNum = (float)(rand() % 10);
		randomNum = (randomNum - 5.0f);
		std::cout << randomNum << "\n";
		m_ball.SetVelocity(sf::Vector2f(-15, randomNum));
		m_playState = TOWARD_PLAYER_ONE;
	}
	return IN_GAME;
}

GAME_STATE PongGame::UpdateTowardP1() {
	//ball movement
	m_ball.SetPosition(sf::Vector2f(m_ball.GetPosition().x + m_ball.GetVelocity().x, m_ball.GetPosition().y + m_ball.GetVelocity().y));
	//ball bounce
	sf::Vector2f bounceVect1 = CollisionHandler::DetectBallCollision(m_ball.GetBall(), m_ball.GetVelocity(), m_playerOne.GetSize(), m_playerOne.GetPosition(), true);
	sf::Vector2f bounceVect2 = CollisionHandler::DetectBallCollision(m_ball.GetBall(), m_ball.GetVelocity(), m_playerTwo.GetSize(), m_playerTwo.GetPosition(), true);
	sf::Vector2f bounceVect3 = CollisionHandler::DetectBallCollision(m_ball.GetBall(), m_ball.GetVelocity(), m_upperWall, m_upperWall.getPosition(), false);
	sf::Vector2f bounceVect4 = CollisionHandler::DetectBallCollision(m_ball.GetBall(), m_ball.GetVelocity(), m_lowerWall, m_lowerWall.getPosition(), false);
	sf::Vector2f bounceVect5 = CollisionHandler::DetectBallCollision(m_ball.GetBall(), m_ball.GetVelocity(), m_p1_goal, m_p1_goal.getPosition(), true);
	sf::Vector2f bounceVect6 = CollisionHandler::DetectBallCollision(m_ball.GetBall(), m_ball.GetVelocity(), m_p2_goal, m_p2_goal.getPosition(), true);

	if (bounceVect1 != sf::Vector2f(0.0f, 0.0f)) {
		m_ball.SetVelocity(bounceVect1);
	}
	if (bounceVect2 != sf::Vector2f(0.0f, 0.0f)) {
		m_ball.SetVelocity(bounceVect2);
	}
	if (bounceVect3 != sf::Vector2f(0.0f, 0.0f)) {
		m_ball.SetVelocity(bounceVect3);
	}
	if (bounceVect4 != sf::Vector2f(0.0f, 0.0f)) {
		m_ball.SetVelocity(bounceVect4);
	}
	if (bounceVect5 != sf::Vector2f(0.0f, 0.0f)) {
		return ScoreP1();
	}
	if (bounceVect6 != sf::Vector2f(0.0f, 0.0f)) {
		return ScoreP2();
	}

	return IN_GAME;
}

GAME_STATE PongGame::UpdateTowardP2() {
	//ball movement
	m_ball.SetPosition(sf::Vector2f(m_ball.GetPosition().x + m_ball.GetVelocity().x, m_ball.GetPosition().y + m_ball.GetVelocity().y));
	//ball bounce
	sf::Vector2f bounceVect1 = CollisionHandler::DetectBallCollision(m_ball.GetBall(), m_ball.GetVelocity(), m_playerOne.GetSize(), m_playerOne.GetPosition(), true);
	sf::Vector2f bounceVect2 = CollisionHandler::DetectBallCollision(m_ball.GetBall(), m_ball.GetVelocity(), m_playerTwo.GetSize(), m_playerTwo.GetPosition(), true);
	sf::Vector2f bounceVect3 = CollisionHandler::DetectBallCollision(m_ball.GetBall(), m_ball.GetVelocity(), m_upperWall, m_upperWall.getPosition(), false);
	sf::Vector2f bounceVect4 = CollisionHandler::DetectBallCollision(m_ball.GetBall(), m_ball.GetVelocity(), m_lowerWall, m_lowerWall.getPosition(), false);
	sf::Vector2f bounceVect5 = CollisionHandler::DetectBallCollision(m_ball.GetBall(), m_ball.GetVelocity(), m_p1_goal, m_p1_goal.getPosition(), true);
	sf::Vector2f bounceVect6 = CollisionHandler::DetectBallCollision(m_ball.GetBall(), m_ball.GetVelocity(), m_p2_goal, m_p2_goal.getPosition(), true);

	if (bounceVect1 != sf::Vector2f(0.0f, 0.0f)) {
		m_ball.SetVelocity(bounceVect1);
	}
	if (bounceVect2 != sf::Vector2f(0.0f, 0.0f)) {
		m_ball.SetVelocity(bounceVect2);
	}
	if (bounceVect3 != sf::Vector2f(0.0f, 0.0f)) {
		m_ball.SetVelocity(bounceVect3);
	}
	if (bounceVect4 != sf::Vector2f(0.0f, 0.0f)) {
		m_ball.SetVelocity(bounceVect4);
	}
	if (bounceVect5 != sf::Vector2f(0.0f, 0.0f)) {
		return ScoreP1();
	}
	if (bounceVect6 != sf::Vector2f(0.0f, 0.0f)) {
		return ScoreP2();
	}

	return IN_GAME;
}

GAME_STATE PongGame::Update(float elapsedMilliseconds) {
	switch (m_playState) {
	case (SERVE_PLAYER_ONE): {
		return ServeP1();
		break;
	}
	case (SERVE_PLAYER_TWO): {
		return ServeP2();
		break;
	}
	case (TOWARD_PLAYER_ONE): {
		return UpdateTowardP1();
		break;
	}
	case (TOWARD_PLAYER_TWO): {
		return UpdateTowardP1();
		break;
	}
	default: {
		return MENU;
		break;
	}
	}
	
}

void PongGame::Render(float elapsedMilliseconds, sf::RenderWindow* window) {
	window->clear();
	//Draw order matters, will draw on top of last shape!
	window->draw(m_upperWall);
	window->draw(m_lowerWall);
	window->draw(m_p1_goal);
	window->draw(m_p2_goal);
	window->draw(m_p1_score);
	window->draw(m_p2_score);
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