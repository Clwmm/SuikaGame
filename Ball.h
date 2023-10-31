#pragma once
#include "Entity.h"

class Ball : public Entity
{
public:
	Ball();
	Ball(const float& radius, const sf::Vector2f& position, std::string texture_link);
	void update(float deltaTime) override;
	virtual Entity* createNext(const sf::Vector2f& position) = 0;
};

