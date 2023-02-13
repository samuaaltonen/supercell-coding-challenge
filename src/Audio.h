#pragma once

#include <SFML/Audio.hpp>
#include "Constants.h"

class Audio
{
public:
	Audio();
	bool	initialise();
	void	playMusic();
	void	playSound(Sounds sound);
	float	getVolume() const { return m_volume; }
	void	setVolume(float volume);

private:
	float				m_volume;
	sf::Music			m_music;
	sf::SoundBuffer		m_bufferScore;
	sf::SoundBuffer		m_bufferTakeDamage;
	sf::Sound			m_soundScore;
	sf::Sound			m_soundTakeDamage;
};