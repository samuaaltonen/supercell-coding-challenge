#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Color.hpp>

class Game;

class Ball : public sf::Drawable, public sf::Transformable
{
public:
	Ball(Game* pGame);
	~Ball();

	bool			initialise();
	void			update(float deltaTime);
	void			draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void			fireFromCenter();
	sf::Vector2f	getVelocity() const { return m_velocity; }
	bool			isMissed() const { return m_missed; }

private:
	Game* m_pGame;
	sf::Vector2f    m_velocity;
	bool            m_missed;
	sf::Color       m_color;
};
