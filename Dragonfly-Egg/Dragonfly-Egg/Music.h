#pragma once
#include <string>
#include <SFML/Audio.hpp>

namespace df {
	class Music {
	private:
		sf::Music music;
		std::string label;
		Music(Music const&);
		void operator=(Music const&);

	public:
		Music();

		int loadMusic(std::string filename);

		void setLabel(std::string new_label);

		std::string getlabel() const;

		void play(bool loop = true);

		void stop();

		void pause();

		sf::Music* getMusic();
	};
}

