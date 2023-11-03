#pragma once
#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include "Manager.h"
#include "Event.h"

const int FRAME_TIME_DEFAULT = 33;

// Two-letter acronym for easier access to manager.
#define GM df::GameManager::getInstance()

namespace df {

	// Default frame time (game loop time) in milliseconds (33 ms == 30 f/s).
	const int FRAME_TIME_DEFAULT = 33;

	class GameManager : public Manager {

	private:
		GameManager();                      // Private since a singleton.
		GameManager(GameManager const&);    // Don't allow copy.
		void operator=(GameManager const&); // Don't allow assignment.
		bool m_game_over;           // game loop should stop.
		int m_frame_time;           // Target time per game loop, in millisec.

	public:
		// Get the singleton instance of the GameManager.
		static GameManager& getInstance();

		// Startup all GameManager services.
		int startUp();

		// Shut down GameManager services.
		void shutDown();

		// Run game loop.
		void run();

		// Set game over status to indicated value.
		// If true (default), will stop game loop.
		void setGameOver(bool game_over = true);

		// Get game over status.
		bool getGameOver() const;

		// Return frame time.  
		// Frame time is target time for each game loop, in milliseconds.
		int getFrameTime() const;

		int onEvent(const Event* p_event);
	};

} // end of namespace df
#endif // __GAME_MANAGER_H__
