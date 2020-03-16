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



bool PongMenu::PollInput(sf::Vector2i mousePosition, Button* button) {
	float halfWidth = (button->GetRect().getSize().x / 2);
	float halfHeight = (button->GetRect().getSize().y / 2);
	float distX = abs(mousePosition.x - (button->GetRect().getPosition().x + halfWidth));
	float distY = abs(mousePosition.y - (button->GetRect().getPosition().y + halfHeight));
	if ((distX <= halfWidth) && (distY <= halfHeight)) {
		button->SetState(Button::HOVER);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			button->SetState(Button::DOWN);
			return true;
		}
	}
	else {
		button->SetState(Button::UP);
	}
	return false;
}

GAME_STATE PongMenu::Update(float millisecs, sf::RenderWindow* window, sf::Vector2i mousePosition) {
	bool playButtonPressed = PollInput(mousePosition, &m_playButton);
	bool exitButtonPressed = PollInput(mousePosition, &m_exitButton);
	if (playButtonPressed) {
		return IN_GAME;
	}
	else { return MENU; }
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
