#include "Entity.h"

void Entity::draw(sf::RenderWindow& window)
{
	//this->shape.setPosition(this->position.x, this->position.y);
	this->sprite.setPosition(this->position.x, this->position.y);

	//window.draw(this->shape);
	window.draw(this->sprite);
}

Entity::~Entity()
{
}
