#pragma once
#include "TextureManager.h"
#include <iostream>

class Entity
{
public:
	sf::Sprite sprite;
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;

	float radius;
	float mass;
	float rotation;

	bool life = true;

	virtual void draw(sf::RenderWindow& window);
	virtual void update(float deltaTime) = 0;
	virtual Entity* createNext(const sf::Vector2f& position) = 0;
	virtual ~Entity();
};

