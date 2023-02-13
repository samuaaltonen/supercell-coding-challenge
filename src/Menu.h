#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "Constants.h"
#include "Game.h"
#include "Pitch.h"

class Game;

class Menu : public sf::Drawable
{
public:
	Menu(Game* pGame);
	~Menu();

	bool		initialise();
	void		update(float deltaTime);
	void		draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	Game* m_pGame;
	sf::Texture			m_bgTexture;
	sf::RectangleShape	m_bg;
	sf::RectangleShape	m_shadow;
};