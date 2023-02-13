#include "ControllerAI.h"

#include <algorithm>
#include <SFML/System.hpp>
#include "Game.h"
#include "Pitch.h"
#include "Paddle.h"
#include <math.h>

ControllerAI::ControllerAI(Game* pGame, Paddle* pPaddle)
    : Controller(pGame, pPaddle)
{
    
}

ControllerAI::~ControllerAI()
{
    
}

bool ControllerAI::initialise()
{
    m_pClock = std::make_unique<sf::Clock>();
    m_targetLocationY = 0.f;
    return true;
}

void ControllerAI::update(float deltaTime)
{
    if (m_pClock->getElapsedTime().asSeconds() >= 1.f)
    {
        const sf::Vector2f& pitchSize = m_pGame->getPitch()->getPitchSize();
        m_targetLocationY = (rand() % 100)*0.01f * (pitchSize.y-m_pPaddle->getPaddleHeight());
        m_pClock->restart();
    }
    
    const float paddlePositionY = m_pPaddle->getPosition().y;
    const float offsetFromTarget = m_targetLocationY - paddlePositionY;
    if (fabs(offsetFromTarget) > 1.f)
    {
        const float maxMovement = PaddleMoveSpeed*deltaTime;
        const float movement = std::min(fabs(offsetFromTarget), maxMovement);
        m_pPaddle->move(offsetFromTarget < 0.f ? -movement : movement);
    }
}
