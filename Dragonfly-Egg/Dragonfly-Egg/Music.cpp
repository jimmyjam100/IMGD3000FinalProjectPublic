#include "Music.h"

namespace df {
	void Music::operator=(Music const&)
	{
	}
	Music::Music()
	{
		label = "";
	}

	int Music::loadMusic(std::string filename)
	{
		music.openFromFile(filename);
		return 0;
	}

	void Music::setLabel(std::string new_label)
	{
		label = new_label;
	}

	std::string Music::getlabel() const
	{
		return label;
	}

	void Music::play(bool loop)
	{
		music.setLoop(loop);
		music.play();
	}

	void Music::stop()
	{
		music.stop();
	}

	void Music::pause()
	{
		music.pause();
	}

	sf::Music* Music::getMusic()
	{
		return &music;
	}

}
