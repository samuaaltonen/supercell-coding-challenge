#pragma once

#include <SFML/Audio.hpp>
#include "Constants.h"

class Audio
{
public:
	Audio();
	~Audio();

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
	sf::SoundBuffer		m_bufferGoal;
	sf::Sound			m_soundScore;
	sf::Sound			m_soundTakeDamage;
	sf::Sound			m_soundGoal;
};