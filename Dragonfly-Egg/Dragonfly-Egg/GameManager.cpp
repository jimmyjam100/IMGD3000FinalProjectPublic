#include "GameManager.h"
#include "Clock.h"
#include <time.h>
#define NOMINMAX
#include <windows.h>
#include <chrono>
#include <thread>
#include "WorldManager.h"
#include "LogManager.h"
#include "EventStep.h"
#include "DisplayManager.h"
#include "InputManager.h"


namespace df {

	GameManager::GameManager() {
		m_frame_time = FRAME_TIME_DEFAULT;
		m_game_over = false;
	}

	void GameManager::operator=(GameManager const&){
		
	}

	GameManager& GameManager::getInstance()
	{
		static GameManager single;
		return single;
	}

	int GameManager::startUp()
	{
		LM.startUp();
		if (isStarted()) {
			LM.writeLog("ERROR: Game Manager is already Started");
			return -1;
		}
		LM.writeLog("Starting Up Game Manger");
		WM.startUp();
		DM.startUp();
		IM.startUp();

		//timeBeginPeriod(1);
		m_game_over = false;
		return Manager::startUp();
	}

	void GameManager::shutDown()
	{
		LM.writeLog("Shutting down Game Manager");
		WM.shutDown();
		LM.shutDown();
		DM.shutDown();
		m_game_over = true;
		Manager::shutDown();
	}

	void GameManager::run()
	{
		LM.writeLog("Running the game");
		if (!isStarted() || !WM.isStarted()) {
			LM.writeLog("ERROR: Can't run the game untill both world and game manager are running");
			return;
		}
		Clock clock = Clock();
		EventStep *es = new EventStep();
		long adjustTime = 0;
		while (!m_game_over) {
			clock.delta();
			IM.getInput();
			onEvent(es);
			es->setStepCount(es->getStepCount() + 1);
			WM.update();
			WM.draw();
			DM.swapBuffers();
			long loop_time = clock.split();
			//std::cout << loop_time << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(m_frame_time - loop_time - adjustTime));
			if (m_frame_time-adjustTime < loop_time) {
				adjustTime = loop_time - (m_frame_time);
			}
			else {
				adjustTime = 0;
			}
		}

		//while loop
			//get input
			//update world
			//render world
			//delta time
			//sleep for time
		//end while loop
	}

	void GameManager::setGameOver(bool game_over)
	{
		LM.writeLog("Seting Game Over State");
		m_game_over = game_over;
	}

	bool GameManager::getGameOver() const
	{
		return m_game_over;
	}

	int GameManager::getFrameTime() const
	{
		return m_frame_time;
	}
	int GameManager::onEvent(const Event* p_event)
	{
		int count = 0;
		std::vector<Object*> all_objs = WM.getAllObjects();
		std::vector<Object*>::iterator it = all_objs.begin();
		while (it != all_objs.end()) {
			(*it)->eventHandler(p_event);
			++it;
			++count;
		}
		return count;
	}
}

