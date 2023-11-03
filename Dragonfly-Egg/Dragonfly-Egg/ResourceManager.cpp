#include "ResourceManager.h"
#include "LogManager.h"

namespace df {

	ResourceManager::ResourceManager(ResourceManager const&) {

	}

	ResourceManager::ResourceManager() {
		//for (Sound s : sound) {
			//s = Sound();
		//}
		sound_count = 0;
		music_count = 0;
	}

	void ResourceManager::operator=(ResourceManager const&)
	{
	}

	ResourceManager& ResourceManager::getInstance()
	{
		static ResourceManager single;
		return single;
	}
	int ResourceManager::loadSound(std::string filename, std::string label)
	{
		if (sound_count == MAX_SOUNDS) {
			LM.writeLog("sound array full");
			return -1;
		}
		if (sound[sound_count].loadSound(filename) == -1) {
			LM.writeLog("Unable to load from file");
			return -1;
		}
		sound[sound_count].setLabel(label);
		++sound_count;
		return 0;
	}
	int ResourceManager::unloadSound(std::string label)
	{
		for (int i = 0; i < sound_count; ++i) {
			if (sound[i].getLabel() == label) {
				sound[i] = sound[sound_count - 1];
				sound[sound_count - 1] = Sound();
				--sound_count;
				return 0;
			}
		}
		return -1;
	}
	Sound* ResourceManager::getSound(std::string label)
	{
		for (int i = 0; i < sound_count; ++i) {
			if (sound[i].getLabel() == label) {
				return &sound[i];
			}
		}
		return nullptr;
	}
	int ResourceManager::loadMusic(std::string filename, std::string label)
	{
		if (music_count == MAX_MUSICS) {
			LM.writeLog("music array full");
			return -1;
		}
		if (music[music_count].loadMusic(filename) == -1) {
			LM.writeLog("Unable to load from file");
			return -1;
		}
		music[music_count].setLabel(label);
		++music_count;
		return 0;
	}
	int ResourceManager::unloadMusic(std::string label)
	{
		for (int i = 0; i < music_count; ++i) {
			if (music[i].getlabel() == label) {
				return 0; //TODO: remove music
			}
		}
		return -1;
	}
	Music* ResourceManager::getMusic(std::string label)
	{
		for (int i = 0; i < music_count; ++i) {
			if (music[i].getlabel() == label) {
				return &music[i];
			}
		}
		return nullptr;
	}
}

