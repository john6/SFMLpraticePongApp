#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <ctime>    
#include "PongGame.h"
#include "PongMenu.h"
#include "GAME_STATE.h"

int main()
{
	typedef std::chrono::high_resolution_clock hiResTime;
	typedef std::chrono::milliseconds ms;
	typedef std::chrono::high_resolution_clock::time_point time_point;
	std::cout << "IDK1 \n";
	PongGame game(5);
	PongMenu menu = PongMenu();
	GAME_STATE state = MENU;
	sf::RenderWindow window(sf::VideoMode(1500, 900), "SFML works!");
	time_point prevTime = hiResTime::now();
	time_point currTime = hiResTime::now();
	const ms UPDATE_INTERVAL(1);
	ms lag(0);

	while (window.isOpen())
	{
		std::cout << "IDK2 \n";
		prevTime = currTime;
		currTime = hiResTime::now();
		ms currInterval = std::chrono::duration_cast<std::chrono::milliseconds>(currTime - prevTime);
		lag += currInterval;
		if (lag > UPDATE_INTERVAL) {
			sf::Event currEvent;
			std::cout << "IDK3 \n";
			if ((window.pollEvent(currEvent)) && (currEvent.type == sf::Event::Closed)) { window.close(); }

			switch (state) {
			case MENU: {
				sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
				state = menu.Update(1.0f, &window, mousePosition);
				menu.Render(1.0f, &window);
				break;
			}
			case IN_GAME: {
				game.PollKeys();
				state = game.Update(1.0f);
				game.Render(1.0f, &window);
				break;
			}
			}
			lag -= UPDATE_INTERVAL;
			lag = ms(0);
		}
	}
	return 0;
}