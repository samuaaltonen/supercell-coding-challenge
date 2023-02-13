#include "Game.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

#include "Menu.h"
#include "Pitch.h"
#include "Paddle.h"
#include "Ball.h"
#include "ControllerInput.h"
#include "ControllerAI.h"
#include "resources/Resources.h"

Game::Game()
	: m_pPitch(std::make_unique<Pitch>(this))
	, m_pMenu(std::make_unique<Menu>(this))
	, m_state(State::MENU)
	, m_pClock(std::make_unique<sf::Clock>())
{
	m_pPaddles[Side::LEFT] = std::make_unique<Paddle>(this);
	m_pPaddles[Side::RIGHT] = std::make_unique<Paddle>(this);

	m_controllers[Side::LEFT] = std::make_unique<ControllerInput>(this, m_pPaddles[0].get());
	m_controllers[Side::RIGHT] = std::make_unique<ControllerAI>(this, m_pPaddles[1].get());

	m_score[Side::LEFT] = 0.f;
	m_score[Side::RIGHT] = 0.f;

	m_renderScore[Side::LEFT] = 0.f;
	m_renderScore[Side::RIGHT] = 0.f;

	m_spawnTimer = 0.f;
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

	if (!audio.initialise())
		return false;

	m_pClock->restart();

	std::string assetPath = Resources::getAssetPath();
	if (!font.loadFromFile(assetPath + "monogram.ttf"))
	{
		std::cerr << "Unable to load font" << std::endl;
		return false;
	}

	if (!ui_texture.loadFromFile(assetPath + "ui.png"))
	{
		std::cerr << "Unable to load ui textures" << std::endl;
		return false;
	}

	if (!m_pMenu->initialise())
		return false;

	return true;
}

void Game::update(float deltaTime)
{
	switch (m_state)
	{
		case State::MENU:
			m_pMenu->update(deltaTime);
			return;

		case State::GAMEOVER:
			return;
	}

	this->_spawnBalls(deltaTime);
	this->_clearScoredBalls();
	m_pPitch->update(deltaTime);
	m_pPaddles[Side::LEFT]->update(deltaTime);
	m_pPaddles[Side::RIGHT]->update(deltaTime);
	m_controllers[Side::LEFT]->update(deltaTime);
	m_controllers[Side::RIGHT]->update(deltaTime);
	for (Ball& ball : balls)
	{
		ball.update(deltaTime);
	}

	// Update rendering scores
	if (m_score[Side::LEFT] - m_renderScore[Side::LEFT] >= 0.f)
		m_renderScore[Side::LEFT] += RenderScoreIncreaseRate * deltaTime * (m_score[Side::LEFT] - m_renderScore[Side::LEFT]);
	if (m_score[Side::RIGHT] - m_renderScore[Side::RIGHT] >= 0.f)
		m_renderScore[Side::RIGHT] += RenderScoreIncreaseRate * deltaTime * (m_score[Side::RIGHT] - m_renderScore[Side::RIGHT]);

	audio.playMusic();
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*m_pPitch.get());
	target.draw(*m_pPaddles[Side::LEFT].get());
	target.draw(*m_pPaddles[Side::RIGHT].get());
	for (const Ball& ball : balls)
	{
		ball.draw(target, states);
	}

	// draw the score
	sf::Text leftScore;
	leftScore.setFont(font);
	leftScore.setString(std::to_string((int)m_renderScore[Side::LEFT]));
	leftScore.setFillColor(sf::Color::White);
	leftScore.setPosition(target.getSize().x * 0.25f, 10.f);
	leftScore.setStyle(sf::Text::Bold);
	target.draw(leftScore);

	leftScore.setString(std::to_string((int)m_renderScore[Side::RIGHT]));
	leftScore.setPosition(target.getSize().x * 0.75f, 10.f);
	target.draw(leftScore);

	if (m_state == State::MENU)
		target.draw(*m_pMenu.get());
}

void Game::addScore(Side side, float amount)
{
	m_score[side] += amount;
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
	if (key == sf::Keyboard::Escape)
		exit(EXIT_SUCCESS);
}

/**
* Spawn new balls.
*/
void Game::_spawnBalls(float deltaTime)
{
	if (balls.size() >= MaxBalls)
		return;

	m_spawnTimer += deltaTime;
	if (m_spawnTimer < BallRelativeSpawnTime * (float)(balls.size() + 1))
		return;

	Ball    ball(this);

	ball.initialise();
	ball.fireFromCenter();
	balls.push_back(ball);
	m_spawnTimer = 0.f;
}

/**
* Clear balls that have already scored.
*/
void Game::_clearScoredBalls()
{
	while (true)
	{
		auto iterator = std::find_if(balls.begin(), balls.end(), [](const Ball& ball) {
			return ball.isMissed();
			});

		// Stop clearing when iterator returns end
		if (iterator == balls.end())
			return;

		// Erase the ball
		balls.erase(iterator);
	}
}

void Game::changeState(Game::State state)
{
	m_state = state;
}