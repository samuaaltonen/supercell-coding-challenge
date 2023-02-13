#pragma once

#include "Controller.h"

class ControllerInput : public Controller
{
public:
    ControllerInput(Game* pGame, Paddle* pPaddle);
    ~ControllerInput();
    
    virtual void update(float deltaTime) override;
};
