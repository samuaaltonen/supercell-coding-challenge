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

	m_shadow.setSize(sf::Vector2f(500.f, 600.f));
	m_shadow.setFillColor(sf::Color(0, 0, 0, 127));
	m_shadow.setPosition(sf::Vector2f((float)((pitchSize.x - 500) / 2), 50.f));
	return true;
}

void Menu::update(float deltaTime)
{

}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	static const char *control_strings[8] = {
		"Controls:",
		"[Arrow Up / W]          Move paddle up",
		"[Arrow Down / S]       Move paddle down",
		"[Tab]                  Display menu",
		"[Tab / Space]          Start",
		"[+ / PageUp / i]       Volume up",
		"[- / PageDown / k]     Volume down",
		"[Esc]					Exit"
	};
	const sf::Vector2f	pitchSize = m_pGame->getPitch()->getPitchSize();
	sf::Text			text;

	target.draw(m_bg);
	target.draw(m_shadow);

	text.setFont(m_pGame->font);
	text.setString("WELCOME");
	text.setCharacterSize(48);
	text.setFillColor(sf::Color::White);
	text.setPosition(sf::Vector2f((float)((pitchSize.x - 200) / 2), 60.f));
	target.draw(text);

	text.setCharacterSize(24);
	text.setFillColor(sf::Color::White);
	for (int i = 0; i < 8; i++)
	{
		text.setString(control_strings[i]);
		text.setPosition(sf::Vector2f((float)((pitchSize.x - 400) / 2), 150.f + i * 40.f));
		target.draw(text);
	}
}