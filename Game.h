#pragma once

#include <vector>
#include <random>
#include <fstream>
#include <sstream>

#include "Balls.h"


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
	sf::RectangleShape endShape;
	sf::Text endText;

	sf::Font font;
	sf::Text pointText;
	sf::Text noPointsText;
	sf::Text nextText;

	size_t noPoints = 0;
	size_t highScore = 0;

	bool renderThread = true;
	sf::Mutex mutex;

public:
	Game(const unsigned int& screen_size);
	~Game();

	static void SaveTexturesToFile(const std::map<std::string, sf::Texture>& textures, const std::string& filename);
	
private:
	void game();
	void updatingEntities();
	void collisions();
	void physics();
	void render();
	void renderTh();
	void createNext(Entity*& first, Entity*& second);
	void blackHole();
	void initActualAndNext();
	void updateActualPosition(const sf::Vector2f& position);
	void pushToGame(std::mt19937& mt, std::uniform_int_distribution<int>& distEntity);
	bool isEntityOverEndBound(Entity* entity);
	void updatingEndGame();
	void updateClickDelay();
	void updateText();
	void updateEndText();
	int getHighScore();
	void updateHighScore(const int& highscore);
	std::string encrypt(const std::string& data);
	std::string decrypt(const std::string& data);
	void restartGame();
	void keyboardMoving();
	void clearEntities();


};

