#pragma once

#include <SFML/Graphics/Drawable.hpp>

class Game;

class Pitch : public sf::Drawable
{
public:
    Pitch(Game* pGame);
    ~Pitch();
    
    bool initialise(sf::Vector2f pitchSize);
    void update(float deltaTime);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    
    const sf::Vector2f& getPitchSize() const { return m_pitchSize; }
    
private:
    Game* m_pGame;
    sf::Vector2f m_pitchSize;
};
