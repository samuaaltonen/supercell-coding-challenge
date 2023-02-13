#include "Audio.h"
#include "resources/Resources.h"

Audio::Audio()
	: m_volume(DefaultVolume)
{
}

Audio::~Audio()
{
}

bool	Audio::initialise()
{
	std::string assetPath = Resources::getAssetPath();

	if (!m_music.openFromFile(assetPath + "BinaryChaos.ogg"))
		return false;
	m_music.setVolume(m_volume);
	m_music.setLoop(true);
	if (!m_bufferScore.loadFromFile(assetPath + "GetAPowerUp.wav"))
		return false;
	if (!m_bufferTakeDamage.loadFromFile(assetPath + "ShotMeDown.wav"))
		return false;
	if (!m_bufferGoal.loadFromFile(assetPath + "DigitalLaugh.wav"))
		return false;
	m_soundScore.setVolume(m_volume / 10.f);
	m_soundTakeDamage.setVolume(m_volume);
	m_soundGoal.setVolume(m_volume);
	return true;
}

void	Audio::playMusic()
{
	if (m_music.getStatus() != sf::Music::Status::Playing)
		m_music.play();
}

void	Audio::playSound(Sounds sound)
{
	switch (sound)
	{
	case Sounds::SOUND_SCORE:
		m_soundScore.setBuffer(m_bufferScore);
		m_soundScore.play();
		break;
	case Sounds::SOUND_TAKE_DAMAGE:
		m_soundTakeDamage.setBuffer(m_bufferTakeDamage);
		m_soundTakeDamage.play();
		break;
	case Sounds::SOUND_GOAL:
		m_soundGoal.setBuffer(m_bufferGoal);
		m_soundGoal.play();
		break;
	}
}

void	Audio::setVolume(float volume)
{
	m_volume = volume;
	m_music.setVolume(m_volume);
	m_soundScore.setVolume(m_volume / 10.f);
	m_soundTakeDamage.setVolume(m_volume);
}