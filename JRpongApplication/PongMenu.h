#pragma once
#include "Button.h"
#include "GAME_STATE.h"
#include <SFML/Graphics.hpp>

class PongMenu
{
private:
	Button m_playButton;
	Button m_exitButton;
	bool m_shouldExit;
	bool m_shouldStart;

public:
	PongMenu();
	~PongMenu();

	GAME_STATE PollInput(sf::Vector2i mousePosition);

	GAME_STATE Update(float millisecs, sf::RenderWindow* window, sf::Vector2i mousePosition);

	void Render(float elapsedMilliseconds, sf::RenderWindow* window);
};

