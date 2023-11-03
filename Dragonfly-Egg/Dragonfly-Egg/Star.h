#pragma once
#include "Object.h"
#include "Event.h"
#include "EventCollision.h"

class Star : public df::Object {
private:
	int m_twinkle_counter;

public:
	Star();
	int draw();
	void setStartPosition();
};