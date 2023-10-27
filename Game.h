#pragma once

#include <iostream>
#include <vector>
#include <random>

#include "Ball.h"


class Game
{
private:
	
	sf::RenderWindow* window = nullptr;
	sf::View view;

	sf::Color backgroundColor;

	sf::Vector2f screenSize;
	sf::Vector2f viewSize;
	float deltaTime = 0;
	sf::Clock clock;

	std::vector<Entity*> entities;

public:
	Game();
	~Game();

	void game();
};

