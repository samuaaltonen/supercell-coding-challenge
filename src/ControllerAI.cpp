#include "ControllerAI.h"

#include <algorithm>
#include <SFML/System.hpp>
#include "Game.h"
#include "Pitch.h"
#include "Paddle.h"
#include "Ball.h"
#include "MathUtils.h"

ControllerAI::ControllerAI(Game* pGame, Paddle* pPaddle)
	: Controller(pGame, pPaddle)
{
}

ControllerAI::~ControllerAI()
{

}

bool ControllerAI::initialise()
{
	return true;
}

void ControllerAI::update(float deltaTime)
{
	sf::Vector2f	paddleCenter = m_pPaddle->getPosition() + sf::Vector2f(0.f, PaddleHeight / 2.f);
	sf::Vector2f	target;
	float			collisionTime;
	float			distance;
	float			speed;

	_determineTarget(&target, &collisionTime);
	if (collisionTime < 0.f)
		return;
	distance = VecLength(target - paddleCenter);

	// No need to move when distance close enough to hit paddle anyways
	if (distance < PaddleHeight / 2.f)
		return;

	speed = PaddleMoveSpeed;

	// Check if we need to use boost
	if (m_pGame->getDifficulty() > AIUseBoostDifficultyThreshold
		&& distance >= collisionTime * PaddleMoveSpeed)
	{
		speed *= BoostMultiplier;
		m_pPaddle->boost(deltaTime);
	}

	// Dampen speed based on difficulty (maximum difficulty = no dampening = inhuman reactions)
	speed *= m_pGame->getDifficulty() / MaxAIDifficulty;

	// Move the paddle
	if (target.y < paddleCenter.y)
		m_pPaddle->move(-speed * deltaTime);
	else
		m_pPaddle->move(speed * deltaTime);
}

/**
 * Calculates most threatening ball based on ball velocities, directions and positions.
 */
void    ControllerAI::_determineTarget(sf::Vector2f* target, float* collisionTime)
{
	const sf::Vector2f&	pitchSize = m_pGame->getPitch()->getPitchSize();
	Line2f				paddleLine = {m_pPaddle->getPosition(), m_pPaddle->getPosition() + sf::Vector2f(0.f, PaddleHeight)};
	Line2f				pitchTop = { sf::Vector2f(0.f, 0.f), sf::Vector2f(pitchSize.x, 0.f)};
	Line2f				pitchBottom = { sf::Vector2f(0.f, pitchSize.y), sf::Vector2f(pitchSize.x, pitchSize.y)};
	sf::Vector2f		intersection;

	// Mark time as negative to know that there is no threat
	*collisionTime = -1.f;

	// Check balls
	for (Ball& ball : m_pGame->balls)
	{
		if (ball.getVelocity().x <= 0.f)
			continue;

		sf::Vector2f	ballStart = ball.getPosition();
		Line2f			ballLine = { ballStart, ballStart + ball.getVelocity() };
		if (!_lineIntersection(paddleLine, ballLine, &intersection))
			continue;
		int		collisionCalculations = -1;
		float	totalTravelTime = 0.f;

		/**
		 * Ping pong intersections from window topand bottom walls. With luck there can
		 * be a ball that has close to 0 horizontal velocity and therefore would ping
		 * pong top/bottom very long, so we only loop until AIExhaustion.
		 */
		while ((intersection.y < 0.f || intersection.y > pitchSize.y)
			&& ++collisionCalculations < AIExhaustion)
		{
			if (intersection.y < 0.f)
			{
				// Get intersection with pitch top
				if (!_lineIntersection(pitchTop, ballLine, &intersection))
					break;
				ballLine.a = intersection;
				ballLine.b = intersection + sf::Vector2f(ball.getVelocity().x, -ball.getVelocity().y);
				// Add travel time (v = x / t => t = x / v)
				totalTravelTime += _getTravelTime(ballStart, intersection, ball.getVelocity());
				ballStart = intersection;
				// Get new intersection point with paddleline
				if (!_lineIntersection(paddleLine, ballLine, &intersection))
					break;
			}
			if (intersection.y > pitchSize.y)
			{
				// Get intersection with pitch bottom
				if (!_lineIntersection(pitchBottom, ballLine, &intersection))
					break;
				ballLine.a = intersection;
				ballLine.b = intersection + sf::Vector2f(ball.getVelocity().x, -ball.getVelocity().y);
				// Add travel time (v = x / t => t = x / v)
				totalTravelTime += _getTravelTime(ballStart, intersection, ball.getVelocity());
				ballStart = intersection;
				// Get new intersection point with paddleline
				if (!_lineIntersection(paddleLine, ballLine, &intersection))
					break;
			}
		}

		// Add travel time (v = x / t => t = x / v)
		totalTravelTime += _getTravelTime(ballStart, intersection, ball.getVelocity());
		if (*collisionTime < 0.f || (*collisionTime > 0.f && totalTravelTime < *collisionTime))
		{
			*collisionTime = totalTravelTime;
			*target = intersection;
		}
	}
}

/**
 * Calculates intersection point for 2 lines. If there is no intersection returns false
 * (usually there is since calculation assumes lines to be infinite).
 * 
 * See also:
 * https://en.wikipedia.org/wiki/Line%E2%80%93line_intersection
 * 
 * (in bigger project this would make sense to be moved to math utils/library)
 */
bool	ControllerAI::_lineIntersection(ControllerAI::Line2f a, ControllerAI::Line2f b, sf::Vector2f* intersection)
{
	double	divider;
	double	x;
	double	y;

	divider = (a.a.x - a.b.x) * (b.a.y - b.b.y)
		- (a.a.y - a.b.y) * (b.a.x - b.b.x);
	if (!divider || !intersection)
		return (false);
	x = (a.a.x * a.b.y - a.a.y * a.b.x) * (b.a.x - b.b.x)
		- (a.a.x - a.b.x) * (b.a.x * b.b.y - b.a.y * b.b.x);
	y = (a.a.x * a.b.y - a.a.y * a.b.x) * (b.a.y - b.b.y)
		- (a.a.y - a.b.y) * (b.a.x * b.b.y - b.a.y * b.b.x);
	intersection->x = x / divider;
	intersection->y = y / divider;
	return (true);
}

float	ControllerAI::_getTravelTime(sf::Vector2f a, sf::Vector2f b, sf::Vector2f velocity)
{
	return (VecLength(b - a) / VecLength(velocity));
}
