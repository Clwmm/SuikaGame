#pragma once
#include "Entity.h"

class Ball : public Entity
{
public:
	Ball(const float& radius, const sf::Vector2f& position);
	~Ball();
	void update(float deltaTime) override;
};

