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
	sf::Vertex topLine[2];

	Entity* actual = nullptr;
	Entity* next = nullptr;

	bool entityOverEndBound = false;
	float endTime = 0.f;

	float clickDelayTime = 0.f;
	bool canClick = true;

	bool gameOver = false;

public:
	Game();
	~Game();

	void game();
	void updatingEntities();
	void collisions();
	void physics();
	void render();
	void createNext(Entity*& first, Entity*& second);
	void initActualAndNext();
	void updateActualPosition(const sf::Vector2f& position);
	void pushToGame(std::mt19937& mt, std::uniform_int_distribution<int>& distEntity);
	bool isEntityOverEndBound(Entity* entity);
	void updatingEndGame();
	void updateClickDelay();
	void clearEntities();
};

