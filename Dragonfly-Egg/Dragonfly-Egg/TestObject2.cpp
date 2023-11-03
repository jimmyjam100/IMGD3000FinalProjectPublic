#include "TestObject2.h"
#include "Vector.h"
#include "DisplayManager.h"

TestObject2::TestObject2()
{
	setPosition(df::Vector(30, 20));
	setType("TestObject2");
	setBox(df::Box(df::Vector(0, 0), 1, 1));
	setSprite("good");
}

int TestObject2::eventHandler(const df::Event* p_e)
{
	return 0;
}

