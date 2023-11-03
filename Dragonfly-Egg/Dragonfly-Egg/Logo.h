#pragma once
#include "Object.h"
#include "Player.h"
#include "EventGamepad.h"

class Logo : public df::Object {
private:
	df::Object* p1;
	df::Object* p2;
	bool isStarted;
	bool held;
	bool nextHeld;
	std::string music_playing;

public:
	void startGame();
	void endGame();
	Logo();
	int eventHandler(const df::Event* p_e);
	void hanndleGamepad(const df::EventGamepad *e);

};