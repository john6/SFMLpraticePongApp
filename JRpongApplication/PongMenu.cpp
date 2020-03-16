#include "PongMenu.h"

PongMenu::PongMenu()
{
	sf::RectangleShape playButtonRect(sf::Vector2f(800, 250));
	playButtonRect.setPosition(sf::Vector2f(200, 100));
	m_playButton = Button("Play", playButtonRect);
	m_playButton.SetColors(sf::Color::Black, sf::Color::White, sf::Color(128, 128, 128));
	sf::RectangleShape exitButtonRect(sf::Vector2f(800, 250));
	exitButtonRect.setPosition(sf::Vector2f(200, 500));
	m_exitButton = Button("Exit", exitButtonRect);
	m_exitButton.SetColors(sf::Color::Black, sf::Color::White, sf::Color(128, 128, 128));

	m_shouldExit = false;
	m_shouldStart = false;
}


PongMenu::~PongMenu()
{
}



GAME_STATE PongMenu::PollInput(sf::Vector2i mousePosition) {

	return MENU;
}

GAME_STATE PongMenu::Update(float millisecs, sf::RenderWindow* window, sf::Vector2i mousePosition) {
	GAME_STATE input = PollInput(mousePosition);
	return MENU;
}


void PongMenu::Render(float elapsedMilliseconds, sf::RenderWindow* window) {
	window->clear();

	window->draw(m_playButton.GetRect());
	window->draw(m_exitButton.GetRect());

	sf::Font font;
	font.loadFromFile("kongtext.ttf");

	sf::Text play = m_playButton.GetText();
	play.setFont(font);
	window->draw(play);

	sf::Text exit = m_exitButton.GetText();
	exit.setFont(font);
	window->draw(exit);


	window->display();
}
