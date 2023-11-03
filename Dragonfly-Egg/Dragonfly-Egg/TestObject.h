#pragma once
#include "Object.h"
#include "Event.h"
#include "EventKeyboard.h"

class TestObject : public df::Object {
public:
	TestObject();
	int eventHandler(const df::Event* p_e);
	int getId() const; // gets object Id
	void hanndleKeyboard(df::EventKeyboard *ev);
};