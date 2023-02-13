#include "Game.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

#include "Pitch.h"
#include "Paddle.h"
#include "Ball.h"
#include "ControllerInput.h"
#include "ControllerAI.h"
#include "resources/Resources.h"

Game::Game()
    : m_pPitch(std::make_unique<Pitch>(this))
    , m_pBall(std::make_unique<Ball>(this))
    , m_state(State::WAITING)
    , m_pClock(std::make_unique<sf::Clock>())
{
    m_pPaddles[Side::LEFT] = std::make_unique<Paddle>(this);
    m_pPaddles[Side::RIGHT] = std::make_unique<Paddle>(this);
    
    m_controllers[Side::LEFT] = std::make_unique<ControllerInput>(this, m_pPaddles[0].get());
    m_controllers[Side::RIGHT] = std::make_unique<ControllerAI>(this, m_pPaddles[1].get());
    
    m_score[Side::LEFT] = 0;
    m_score[Side::RIGHT] = 0;
}

Game::~Game()
{
    
}

bool Game::initialise(sf::Vector2f pitchSize)
{
    if (!m_pPitch->initialise(pitchSize))
        return false;
    
    if (!m_pPaddles[Side::LEFT]->initialise(Side::LEFT))
        return false;
    if (!m_pPaddles[Side::RIGHT]->initialise(Side::RIGHT))
        return false;
    if (!m_controllers[Side::LEFT]->initialise())
        return false;
    if (!m_controllers[Side::RIGHT]->initialise())
        return false;
    if (!m_pBall->initialise())
        return false;
    
    m_pClock->restart();
    
    std::string assetPath = Resources::getAssetPath();
    if (!m_font.loadFromFile(assetPath + "Lavigne.ttf"))
    {
        std::cerr << "Unable to load font" << std::endl;
        return false;
    }
    
    return true;
}

void Game::update(float deltaTime)
{
    switch (m_state)
    {
        case State::WAITING:
        {
            if (m_pClock->getElapsedTime().asSeconds() >= 3.f)
            {
                m_pBall->fireFromCenter();
                m_state = State::ACTIVE;
            }
        }
            break;
            
        case State::ACTIVE:
            break;
    }
    m_pPitch->update(deltaTime);
    m_pPaddles[Side::LEFT]->update(deltaTime);
    m_pPaddles[Side::RIGHT]->update(deltaTime);
    m_controllers[Side::LEFT]->update(deltaTime);
    m_controllers[Side::RIGHT]->update(deltaTime);
    m_pBall->update(deltaTime);
}

void Game::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(*m_pPitch.get());
    target.draw(*m_pPaddles[Side::LEFT].get());
    target.draw(*m_pPaddles[Side::RIGHT].get());
    target.draw(*m_pBall.get());
    
    // draw the score
    sf::Text leftScore;
    leftScore.setFont(m_font);
    leftScore.setString(std::to_string(m_score[Side::LEFT]));
    leftScore.setFillColor(sf::Color::White);
    leftScore.setPosition(target.getSize().x*0.25f, 10.f);
    leftScore.setStyle(sf::Text::Bold);
    target.draw(leftScore);
    
    leftScore.setString(std::to_string(m_score[Side::RIGHT]));
    leftScore.setPosition(target.getSize().x*0.75f, 10.f);
    target.draw(leftScore);
}

void Game::scoreGoal(Side side)
{
    m_state = State::WAITING;
    m_pClock->restart();
    m_score[side]++;
}

void Game::onKeyPressed(sf::Keyboard::Key key)
{
    m_controllers[Side::LEFT]->onKeyPressed(key);
    m_controllers[Side::RIGHT]->onKeyPressed(key);
}

void Game::onKeyReleased(sf::Keyboard::Key key)
{
    m_controllers[Side::LEFT]->onKeyReleased(key);
    m_controllers[Side::RIGHT]->onKeyReleased(key);
}
