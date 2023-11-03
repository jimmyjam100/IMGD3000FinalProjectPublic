#pragma once
#include "Object.h"
class GameWin : public df::Object {
private:
	Object* top_text;
	Object* bottom_text;

public:
	GameWin(int winning_player);
	~GameWin();
};