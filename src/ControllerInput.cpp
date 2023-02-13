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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
        || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        m_pPaddle->move(-PaddleMoveSpeed*deltaTime);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
        || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        m_pPaddle->move(PaddleMoveSpeed*deltaTime);
    }
}

void ControllerInput::onKeyPressed(sf::Keyboard::Key key)
{
    (void)key;
}

void ControllerInput::onKeyReleased(sf::Keyboard::Key key)
{
    (void)key;
}
