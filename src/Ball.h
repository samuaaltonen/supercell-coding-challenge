#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

class Game;

class Ball : public sf::Drawable, public sf::Transformable
{
public:
    Ball(Game* pGame);
    ~Ball();
    
    bool initialise();
    void update(float deltaTime);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    
    void fireFromCenter();
    
private:
    Game* m_pGame;
    sf::Vector2f m_velocity;
};
