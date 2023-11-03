#pragma once

#include "SpriteResourceManager.h"
#include "Sound.h"
#include "Music.h"

#define RM df::ResourceManager::getInstance()
const int MAX_SOUNDS = 128;
const int MAX_MUSICS = 128;

namespace df {
	class ResourceManager : public SpriteResourceManager {
	private:
		Sound sound[MAX_SOUNDS];
		int sound_count;
		Music music[MAX_MUSICS];
		int music_count;
		ResourceManager();
		ResourceManager(ResourceManager const&);
		void operator=(ResourceManager const&);
	public:
		static ResourceManager& getInstance();

		int loadSound(std::string filename, std::string label);

		int unloadSound(std::string label);

		Sound* getSound(std::string label);

		int loadMusic(std::string filename, std::string label);

		int unloadMusic(std::string label);

		Music* getMusic(std::string label);
	};
}

