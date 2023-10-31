#pragma once

#include <vector>
#include <random>

#include "Strawberry.h"
#include "Apple.h"
#include "Orange.h"
#include "Melon.h"
#include "Watermelon.h"
#include "Final.h"


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
	std::vector<std::pair<Entity*, Entity*>> vecCollidingPairs;

	sf::Sprite glass;

public:
	Game();
	~Game();

	void game();
	void updatingEntities();
	void collisions();
	void physics();
	void render();
	void createNext(Entity*& first, Entity*& second);
	void clearEntities();
};

