#pragma once
#include "SFML/Graphics.hpp"
#include "Settings.h"
#include <iostream>

class Entity
{
public:
	sf::CircleShape shape;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;

	float radius;
	float mass;

	bool life = true;

	virtual void draw(sf::RenderWindow& window);
	virtual void update(float deltaTime) = 0;
	virtual ~Entity();
};

