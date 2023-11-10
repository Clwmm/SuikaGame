#include "Entity.h"

void Entity::draw(sf::RenderWindow& window)
{
	this->sprite.setPosition(this->position.x, this->position.y);
	this->sprite.setRotation(this->rotation);

	window.draw(this->sprite);
}

Entity::~Entity()
{
}
