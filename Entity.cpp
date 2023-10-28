#include "Entity.h"

void Entity::draw(sf::RenderWindow& window)
{
	this->shape.setPosition(this->position.x, this->position.y);

	window.draw(this->shape);
}

Entity::~Entity()
{
}
