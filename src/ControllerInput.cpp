#include "ControllerInput.h"

#include "Paddle.h"

ControllerInput::ControllerInput(Game* pGame, Paddle* pPaddle)
    : Controller(pGame, pPaddle)
    , m_movingUp(false)
{
    
}

ControllerInput::~ControllerInput()
{
    
}

void ControllerInput::update(float deltaTime)
{
    if (m_movingUp)
    {
        m_pPaddle->move(-PaddleMoveSpeed*deltaTime);
    }
    else if (m_movingDown)
    {
        m_pPaddle->move(PaddleMoveSpeed*deltaTime);
    }
}

void ControllerInput::onKeyPressed(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::Up)
    {
        m_movingUp = true;
    }
    else if (key == sf::Keyboard::Down)
    {
        m_movingDown = true;
    }
}

void ControllerInput::onKeyReleased(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::Up)
    {
        m_movingUp = false;
    }
    else if (key == sf::Keyboard::Down)
    {
        m_movingDown = false;
    }
}
