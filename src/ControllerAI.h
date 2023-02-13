#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include "Controller.h"
#include <memory>

namespace sf { class Clock; }

class Game;
class Ball;

class ControllerAI : public Controller
{
public:
	/**
	 * Line struct for AI targetting. Line is determined by 2 points.
	 */
	struct Line2f
	{
		sf::Vector2f	a;
		sf::Vector2f	b;
	};

	ControllerAI(Game* pGame, Paddle* pPaddle);
	~ControllerAI();

	virtual bool initialise() override;
	virtual void update(float deltaTime) override;

private:
	void    _determineTarget(sf::Vector2f* target, float* collisionTime);
	bool	_lineIntersection(ControllerAI::Line2f a, ControllerAI::Line2f b, sf::Vector2f* intersection);
	float	_getTravelTime(sf::Vector2f a, sf::Vector2f b, sf::Vector2f velocity);
};
