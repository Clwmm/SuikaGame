#pragma once
#include "Entity.h"

class Ball : public Entity
{
public:
	Ball();
	Ball(const float& radius, const sf::Vector2f& position);
	void update(float deltaTime) override;
};

