#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <memory>
#include <vector>
#include "Constants.h"
#include "Audio.h"

class Menu;
class Pitch;
class Paddle;
class Ball;
class Game;
class Controller;
class Audio;
namespace sf { class Clock; }

class Game : public sf::Drawable
{
public:
	std::vector<Ball>		balls;
	sf::Texture				ui_texture;
	sf::Font				font;
	Audio					audio;

	enum class State
	{
		MENU,
		GAME,
		GAMEOVER,
	};

	Game();
	~Game();

	bool			initialise(sf::Vector2f pitchSize);
	void			update(float deltaTime);
	void			draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void			addScore(Side side, float amount);

	State			getState() const { return m_state; }
	float			getDifficulty() const { return m_difficulty; }
	Paddle*			getPaddle(Side side) { return m_pPaddles[(int)side].get(); }
	const Pitch*	getPitch() const { return m_pPitch.get(); }
	float			getScore(Side side);

	void			onKeyPressed(sf::Keyboard::Key key);
	void			onKeyReleased(sf::Keyboard::Key key);

	void			changeState(Game::State state);

private:
	float						m_spawnTimer;
	float						m_difficulty;

	std::unique_ptr<Menu>		m_pMenu;
	std::unique_ptr<Pitch>		m_pPitch;
	State						m_state;
	std::unique_ptr<sf::Clock>	m_pClock;

	std::unique_ptr<Paddle>		m_pPaddles[2];
	std::unique_ptr<Controller>	m_controllers[2];
	float						m_score[2];
	float						m_renderScore[2];


	void _spawnBalls(float deltaTime);
	void _clearScoredBalls();
	void _handleRepeatableKeys(float deltaTime);
	void _ballCollisions();
};
