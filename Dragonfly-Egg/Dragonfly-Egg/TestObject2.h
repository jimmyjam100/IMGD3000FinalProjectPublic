#pragma once
#include "Object.h"
#include "Event.h"


class TestObject2 : public df::Object {
public:
	TestObject2();
	int eventHandler(const df::Event* p_e);
};