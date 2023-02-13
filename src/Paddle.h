#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Constants.h"

class Game;
class Audio;


class Paddle : public sf::Drawable, public sf::Transformable
{
public:
	Paddle(Game* pGame);
	~Paddle();

	bool            initialise(Side side);
	void            update(float deltaTime);
	void            draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::FloatRect   getRect() const;
	float           getEnergy() const;
	float           getPaddleHeight() const;
	void			takeDamage();
	void            boost(float deltaTime);
	void            move(float yDelta);

private:
	Game*			m_pGame;
	Side			m_side;
	float			m_energy;
	int				m_health;
	float			m_sinceLastBoost;
};
