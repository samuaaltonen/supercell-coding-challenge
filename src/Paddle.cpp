#include "Paddle.h"

#include <SFML/Graphics.hpp>

#include "Constants.h"
#include "Game.h"
#include "Pitch.h"

Paddle::Paddle(Game* pGame)
    : m_pGame(pGame)
    , m_side(Side::LEFT)
    , m_energy(MaxEnergy)
    , m_health(MaxHealth)
    , m_sinceLastBoost(0.f)
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
    m_sinceLastBoost += deltaTime;

    if (m_sinceLastBoost > EnergyRegenCooldown)
    {
        m_energy += deltaTime * EnergyRegen;
        if (m_energy >= MaxEnergy)
            m_energy = MaxEnergy;
    }
}

void Paddle::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    const sf::Vector2f& pitchSize = m_pGame->getPitch()->getPitchSize();

    // Draw paddle
    sf::RectangleShape paddleRect(sf::Vector2f(PaddleWidth, PaddleHeight));
    paddleRect.setFillColor(sf::Color::White);
    paddleRect.setPosition(getPosition());
    target.draw(paddleRect);

    // Draw health icons
    sf::RectangleShape healthIcon(sf::Vector2f(HeartWidth, HeartHeight));
    healthIcon.setTexture(&m_pGame->ui_texture);
    healthIcon.setTextureRect(sf::IntRect(0, 0, (int)HeartWidth, (int)HeartHeight));

    for (int i = 0; i < m_health; i++)
    {
        healthIcon.setPosition(sf::Vector2f(
            UiMargin + i * (HeartWidth + UiGap) + ((m_side == Side::LEFT) ? 0.f : pitchSize.x / 2),
            pitchSize.y - UiMargin - HeartHeight));
        target.draw(healthIcon);
    }

    // Draw energy icons
    sf::RectangleShape energyIcon(sf::Vector2f(EnergyWidth, EnergyHeight));
    energyIcon.setTexture(&m_pGame->ui_texture);
    energyIcon.setTextureRect(sf::IntRect((int)HeartWidth, 0, (int)EnergyWidth, (int)EnergyHeight));

    for (int i = 0; i < (int)(m_energy / (MaxEnergy / BatteryCount)); i++)
    {
        energyIcon.setPosition(sf::Vector2f(
            UiMargin + i * (EnergyWidth + UiGap) + ((m_side == Side::LEFT) ? EnergyIconOffset : EnergyIconOffset + pitchSize.x / 2),
            pitchSize.y - UiMargin - EnergyHeight));
        target.draw(energyIcon);
    }
}

sf::FloatRect Paddle::getRect() const
{
    return sf::FloatRect(getPosition(), sf::Vector2f(PaddleWidth, PaddleHeight));
}

float Paddle::getPaddleHeight() const
{
    return PaddleHeight;
}

float Paddle::getEnergy() const
{
    return m_energy;
}

void Paddle::boost(float deltaTime)
{
    m_energy -= deltaTime * EnergyUsage;
    if (m_energy <= 0.f)
        m_energy = 0.f;
    m_sinceLastBoost = 0.f;
}

void Paddle::move(float yDelta)
{
    sf::Vector2f position = getPosition();
    position.y += yDelta;
    
    const sf::Vector2f& pitchSize = m_pGame->getPitch()->getPitchSize();
    position.y = std::clamp(position.y, 0.f, pitchSize.y-PaddleHeight);
    
    setPosition(position);
}

void Paddle::takeDamage()
{
    m_health--;
    if (m_health <= 0)
        m_pGame->changeState(Game::State::GAMEOVER);
}