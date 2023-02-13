#include "Pitch.h"

#include <SFML/Graphics.hpp>

#include "Constants.h"

Pitch::Pitch(Game* pGame)
    : m_pGame(pGame)
{
    
}

Pitch::~Pitch()
{
    
}

bool Pitch::initialise(sf::Vector2f pitchSize)
{
    m_pitchSize = pitchSize;
    return true;
}

void Pitch::update(float deltaTime)
{
    
}

void Pitch::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    const float LineWidth = 10.f;
    const float LineHeight = 50.f;
    const float Gap = 30.f;
    
    sf::Vector2f size = target.getView().getSize();
    sf::Vector2f cursor((size.x - LineWidth) * 0.5f, 0.f);
    
    while (cursor.y < size.y)
    {
        sf::RectangleShape rectangle(sf::Vector2f(LineWidth, LineHeight));
        rectangle.setFillColor(sf::Color::White);
        rectangle.setPosition(cursor.x, cursor.y);
        target.draw(rectangle);
        
        cursor.y += LineHeight + Gap;
    }
    
}
