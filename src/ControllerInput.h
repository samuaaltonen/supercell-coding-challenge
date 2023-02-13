#pragma once

#include "Controller.h"

class ControllerInput : public Controller
{
public:
    ControllerInput(Game* pGame, Paddle* pPaddle);
    ~ControllerInput();
    
    virtual void update(float deltaTime) override;
    
    virtual void onKeyPressed(sf::Keyboard::Key key) override;
    virtual void onKeyReleased(sf::Keyboard::Key key) override;
    
private:
    bool m_movingUp;
    bool m_movingDown;
};
