#pragma once
#include "Manager.h"

#define IM df::InputManager::getInstance()
namespace df {
	class InputManager : public Manager {
	private:
		InputManager(); // dont allow constructer
		InputManager(InputManager const&); // dont allow copy
		void operator=(InputManager const&); // dont allow copy

	public:
		static InputManager& getInstance(); // get only instance of input manager

		int startUp(); // start up input manager

		void shutDown(); // shut donw input manager

		void getInput(); // get any inputs and send coorosponding events
	};
}
