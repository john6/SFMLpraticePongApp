#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <ctime>    
#include "PongGame.h"

int main()
{
	
	PongGame game(10);
	sf::RenderWindow window(sf::VideoMode(1500, 900), "SFML works!");

	float UPDATE_INTERVAL = 90000000.0f;
	float lag = 0.0f;

	typedef std::chrono::high_resolution_clock Time;
	typedef std::chrono::milliseconds ms;
	typedef std::chrono::duration<float> fsec;
	auto prevTime = Time::now();

	while (window.isOpen())
	{
		auto currTime = Time::now();
		fsec fs = currTime - prevTime;
		ms d = std::chrono::duration_cast<ms>(fs);
		lag += d.count();
		while (lag > UPDATE_INTERVAL) {
			sf::Event currEvent;
			while (window.pollEvent(currEvent))
			{
				if (currEvent.type == sf::Event::Closed) { window.close(); }
			}
			game.PollKeys();
			game.Update(1.0f);
			game.Render(1.0f, &window);
			lag -= UPDATE_INTERVAL;
		}
	}

	return 0;
}