#include "Audio.h"
#include <iostream>
#include "resources/Resources.h"

Audio::Audio()
	: m_volume(DefaultVolume)
{
}

bool	Audio::initialise()
{
	std::string assetPath = Resources::getAssetPath();

	/*if (!m_music.openFromFile(assetPath + "music.wav"))
		return false;
	m_music.setVolume(m_volume);*/
	if (!m_bufferScore.loadFromFile(assetPath + "GetAPowerUp.wav"))
		return false;
	if (!m_bufferTakeDamage.loadFromFile(assetPath + "FallingDownAgain3.wav"))
		return false;
	m_soundScore.setVolume(m_volume);
	m_soundTakeDamage.setVolume(m_volume);
	return true;
}

void	Audio::playMusic()
{
	m_music.play();
}

void	Audio::playSound(Sounds sound)
{
	switch (sound)
	{
	case Sounds::SOUND_SCORE:
		if (m_soundScore.getStatus() == sf::Sound::Playing)
			return;
		m_soundScore.setBuffer(m_bufferScore);
		m_soundScore.play();
		break;
	case Sounds::SOUND_TAKE_DAMAGE:
		if (m_soundTakeDamage.getStatus() == sf::Sound::Playing)
			return;
		m_soundTakeDamage.setBuffer(m_bufferTakeDamage);
		m_soundTakeDamage.play();
		break;
	}
}

void	Audio::setVolume(float volume)
{
	m_volume = volume;
	m_music.setVolume(m_volume);
	m_soundScore.setVolume(m_volume);
	m_soundTakeDamage.setVolume(m_volume);
}