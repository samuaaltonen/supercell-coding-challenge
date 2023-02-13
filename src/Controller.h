#pragma once

#include <SFML/Window/Keyboard.hpp>

class Game;
class Paddle;

class Controller
{
public:
    Controller(Game* pGame, Paddle* pPaddle) : m_pGame(pGame), m_pPaddle(pPaddle) {}
    virtual ~Controller() {}
    
    virtual bool initialise(){ return true; };
    virtual void update(float deltaTime) {};
    
protected:
    Game* m_pGame;
    Paddle* m_pPaddle;
};
