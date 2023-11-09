#pragma once
#include "Ball.h"

class Ball_XII : virtual public Ball
{
public:
	Ball_XII(const sf::Vector2f& position)
		: Ball(BALL_XII, position, "res/Blackhole48.png") {};
	Entity* createNext(const sf::Vector2f& position) override
	{
		return nullptr;
	};
};

class Ball_XI : virtual public Ball
{
public:
	Ball_XI(const sf::Vector2f& position)
		: Ball(BALL_XI, position, "res/Galaxy44.png") {};
	Entity* createNext(const sf::Vector2f& position) override
	{
		return new Ball_XII(position);
	};
};

class Ball_X : virtual public Ball
{
public:
	Ball_X(const sf::Vector2f& position)
		: Ball(BALL_X, position, "res/Planet42.png") {};
	Entity* createNext(const sf::Vector2f& position) override
	{
		return new Ball_XI(position);
	};
};

class Ball_IX : virtual public Ball
{
public:
	Ball_IX(const sf::Vector2f& position)
		: Ball(BALL_IX, position, "res/Moon40.png") {};
	Entity* createNext(const sf::Vector2f& position) override
	{
		return new Ball_X(position);
	};
};

class Ball_VIII : virtual public Ball
{
public:
	Ball_VIII(const sf::Vector2f& position)
		: Ball(BALL_VIII, position, "res/Beach36.png") {};
	Entity* createNext(const sf::Vector2f& position) override
	{
		return new Ball_IX(position);
	};
};

class Ball_VII : virtual public Ball
{
public:
	Ball_VII(const sf::Vector2f& position)
		: Ball(BALL_VII, position, "res/Basketball32.png") {};
	Entity* createNext(const sf::Vector2f& position) override
	{
		return new Ball_VIII(position);
	};
};

class Ball_VI : virtual public Ball
{
public:
	Ball_VI(const sf::Vector2f& position)
		: Ball(BALL_VI, position, "res/Bawling30.png") {};
	Entity* createNext(const sf::Vector2f& position) override
	{
		return new Ball_VII(position);
	};
};

class Ball_V : virtual public Ball
{
public:
	Ball_V(const sf::Vector2f& position)
		: Ball(BALL_V, position, "res/Tenis26.png") {};
	Entity* createNext(const sf::Vector2f& position) override
	{
		return new Ball_VI(position);
	};
};

class Ball_IV : virtual public Ball
{
public:
	Ball_IV(const sf::Vector2f& position)
		: Ball(BALL_IV, position, "res/Pong22.png") {};
	Entity* createNext(const sf::Vector2f& position) override
	{
		return new Ball_V(position);
	};
};

class Ball_III : virtual public Ball
{
public:
	Ball_III(const sf::Vector2f& position)
		: Ball(BALL_III, position, "res/Eyeball18.png") {};
	Entity* createNext(const sf::Vector2f& position) override
	{
		return new Ball_IV(position);
	};
};

class Ball_II : virtual public Ball
{
public:
	Ball_II(const sf::Vector2f& position)
		: Ball(BALL_II, position, "res/Bilard16.png") {};
	Entity* createNext(const sf::Vector2f& position) override
	{
		return new Ball_III(position);
	};
};

class Ball_I : virtual public Ball
{
public:
	Ball_I(const sf::Vector2f& position)
		: Ball(BALL_I, position, "res/Pea12.png") {};
	Entity* createNext(const sf::Vector2f& position) override
	{
		return new Ball_II(position);
	};
};