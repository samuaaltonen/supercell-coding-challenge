#include "Paddle.h"

#include <SFML/Graphics.hpp>

#include "Constants.h"
#include "Game.h"
#include "Pitch.h"

Paddle::Paddle(Game* pGame)
    : m_pGame(pGame)
{
    
}

Paddle::~Paddle()
{
    
}

bool Paddle::initialise(Side side)
{
    m_side = side;
    
    const sf::Vector2f& pitchSize = m_pGame->getPitch()->getPitchSize();
    const float XPosition = (m_side == Side::LEFT) ? PaddleOffsetFromEdge : pitchSize.x-PaddleOffsetFromEdge-PaddleWidth;
    setPosition(sf::Vector2f(XPosition, pitchSize.y*0.5f));
    
    return true;
}

void Paddle::update(float deltaTime)
{

}

void Paddle::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::RectangleShape paddleRect(sf::Vector2f(PaddleWidth, PaddleHeight));
    paddleRect.setFillColor(sf::Color::White);
    paddleRect.setPosition(getPosition());
    target.draw(paddleRect);
}

sf::FloatRect Paddle::getRect() const
{
    return sf::FloatRect(getPosition(), sf::Vector2f(PaddleWidth, PaddleHeight));
}

float Paddle::getPaddleHeight() const
{
    return PaddleHeight;
}

void Paddle::move(float yDelta)
{
    sf::Vector2f position = getPosition();
    position.y += yDelta;
    
    const sf::Vector2f& pitchSize = m_pGame->getPitch()->getPitchSize();
    position.y = std::clamp(position.y, 0.f, pitchSize.y-PaddleHeight);
    
    setPosition(position);
}

