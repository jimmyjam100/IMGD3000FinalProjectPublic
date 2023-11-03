#include "Sound.h"

namespace df {
	Sound::Sound()
	{
		label = "";
		sound = sf::Sound();
		sound_buffer = sf::SoundBuffer();
	}
	Sound::~Sound()
	{
		sound.resetBuffer();
	}
	int Sound::loadSound(std::string filename)
	{
		if (sound_buffer.loadFromFile(filename) == false) {
			return -1;
		}
		sound.setBuffer(sound_buffer);
		return 0;
	}
	void Sound::setLabel(std::string new_label)
	{
		label = new_label;
	}
	std::string Sound::getLabel() const
	{
		return label;
	}
	void Sound::play(bool loop)
	{
		sound.setLoop(loop);
		sound.play();
	}
	void Sound::stop()
	{
		sound.stop();
	}
	void Sound::pause()
	{
		sound.pause();
	}
	sf::Sound Sound::getSound() const
	{
		return sound;
	}
}

