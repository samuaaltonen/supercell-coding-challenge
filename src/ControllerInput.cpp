#include "ControllerInput.h"

#include "Paddle.h"

ControllerInput::ControllerInput(Game* pGame, Paddle* pPaddle)
    : Controller(pGame, pPaddle)
{
    
}

ControllerInput::~ControllerInput()
{
    
}

void ControllerInput::update(float deltaTime)
{
    float   speed = PaddleMoveSpeed;

    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)
        || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
        && m_pPaddle->getEnergy() > MinEnergyToBoost)
    {
        speed *= BoostMultiplier;
        m_pPaddle->boost(deltaTime);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
        || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        m_pPaddle->move(-speed *deltaTime);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
        || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        m_pPaddle->move(speed *deltaTime);
    }
}
