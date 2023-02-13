#include "Menu.h"
#include <iostream>
#include "resources/Resources.h"

Menu::Menu(Game* pGame)
	: m_pGame(pGame)
{
}

Menu::~Menu()
{
}

bool	Menu::initialise()
{
	std::string			assetPath = Resources::getAssetPath();
	const sf::Vector2f	pitchSize = m_pGame->getPitch()->getPitchSize();

	if (!m_bgTexture.loadFromFile(assetPath + "background.png"))
		exit(NULL);
	m_bg.setTexture(&m_bgTexture);
	m_bg.setSize(pitchSize);
	m_bg.setTextureRect(sf::IntRect(0, 0, m_bgTexture.getSize().x, m_bgTexture.getSize().y));

	m_shadow.setSize(sf::Vector2f(600.f, 700.f));
	m_shadow.setFillColor(sf::Color(0, 0, 0, 180));
	m_shadow.setPosition(sf::Vector2f((float)((pitchSize.x - 600) / 2), 150.f));
	return true;
}

void Menu::update(float deltaTime)
{

}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_pGame->getState() == Game::State::GAMEOVER)
		_drawGameOver(target, states);
	else
		_drawMenuItems(target, states);
}

void Menu::_drawMenuItems(sf::RenderTarget& target, sf::RenderStates states) const
{
	static const char* control_strings[10] = {
		"Controls:",
		"[Arrow Up / W]         Move paddle up",
		"[Arrow Down / S]       Move paddle down",
		"[Esc]                  Display menu",
		"[Space]                Start / Continue",
		"[+ / i]                Volume up",
		"[- / k]                Volume down",
		"[PageUp / o]           Difficulty up",
		"[PageDown / l]         Difficulty down",
		"[Esc in menu]          Exit"
	};
	const sf::Vector2f	pitchSize = m_pGame->getPitch()->getPitchSize();
	sf::Text			text;

	target.draw(m_bg);
	target.draw(m_shadow);

	text.setFont(m_pGame->font);
	text.setString("WELCOME");
	text.setCharacterSize(48);
	text.setFillColor(sf::Color::White);
	text.setPosition(sf::Vector2f((float)((pitchSize.x - 140) / 2), 160.f));
	target.draw(text);

	text.setCharacterSize(32);
	text.setFillColor(sf::Color::White);
	int i = -1;
	while (++i < 10)
	{
		text.setString(control_strings[i]);
		text.setPosition(sf::Vector2f((float)((pitchSize.x - 500) / 2), 250.f + i * 40.f));
		target.draw(text);
	}

	text.setString("Current volume:        " + std::to_string((int)m_pGame->audio.getVolume()) + " / 100");
	text.setFillColor(sf::Color::Green);
	text.setPosition(sf::Vector2f((float)((pitchSize.x - 500) / 2), 280.f + i * 40.f));
	target.draw(text);

	text.setString("Current AI difficulty: " + std::to_string((int)m_pGame->getDifficulty()) + " / 100");
	text.setFillColor(sf::Color(
		(int)(m_pGame->getDifficulty() / MaxAIDifficulty * 255.f),
		(int)((MaxAIDifficulty - m_pGame->getDifficulty()) / MaxAIDifficulty * 255.f),
		0,
		255
	));
	text.setPosition(sf::Vector2f((float)((pitchSize.x - 500) / 2), 320.f + i * 40.f));
	target.draw(text);
}


void Menu::_drawGameOver(sf::RenderTarget& target, sf::RenderStates states) const
{
	const sf::Vector2f	pitchSize = m_pGame->getPitch()->getPitchSize();
	sf::Text			text;

	target.draw(m_bg);
	target.draw(m_shadow);

	text.setFont(m_pGame->font);
	text.setString("GAME OVER");
	text.setCharacterSize(48);
	text.setFillColor(sf::Color::White);
	text.setPosition(sf::Vector2f((float)((pitchSize.x - 140) / 2), 160.f));
	target.draw(text);

	int playerScore = (int)m_pGame->getScore(Side::LEFT);
	int aiScore = (int)m_pGame->getScore(Side::RIGHT);

	text.setString("Your score:   " + std::to_string(playerScore));
	text.setFillColor(playerScore > aiScore ? sf::Color::Green : sf::Color::Red);
	text.setPosition(sf::Vector2f((float)((pitchSize.x - 500) / 2), 280.f));
	target.draw(text);

	text.setString("AI score:     " + std::to_string(aiScore));
	text.setFillColor(sf::Color::White);
	text.setPosition(sf::Vector2f((float)((pitchSize.x - 500) / 2), 320.f));
	target.draw(text);
}
