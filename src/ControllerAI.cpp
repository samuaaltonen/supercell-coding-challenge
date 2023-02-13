#include "ControllerAI.h"

#include <algorithm>
#include <SFML/System.hpp>
#include "Game.h"
#include "Pitch.h"
#include "Paddle.h"
#include "Ball.h"

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
	sf::Vector2f	target;
	float			collisionTime;

	_determineTarget(&target, &collisionTime);
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
	Ball				*threat;

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

		// Ping pong intersections from window top and bottom walls
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
		printf("%f\n", totalTravelTime);
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
	sf::Vector2f	distance = b - a;

	return (sqrtf(distance.x * distance.x + distance.y * distance.y)
		/ sqrtf(velocity.x * velocity.x + velocity.y * velocity.y));
}