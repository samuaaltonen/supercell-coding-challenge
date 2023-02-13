#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include "Constants.h"

class Game;


class Paddle : public sf::Drawable, public sf::Transformable
{
public:
    Paddle(Game* pGame);
    ~Paddle();
    
    bool initialise(Side side);
    void update(float deltaTime);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    
    sf::FloatRect getRect() const;
    float getPaddleHeight() const;
    void move(float yDelta);
    
private:
    Game* m_pGame;
    Side m_side;
};
