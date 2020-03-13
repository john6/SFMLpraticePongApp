#pragma once
#include <SFML/Graphics.hpp>
static class GameRenderer
{
public:
	GameRenderer(sf::Vector2f screenDimensions);
	~GameRenderer();

	void Render(float elapsedMilliseconds);
};