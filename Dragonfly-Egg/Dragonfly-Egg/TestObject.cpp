#include "TestObject.h"
#include "Event.h"
#include "EventStep.h"
#include "GameManager.h"
#include "DisplayManager.h"
#include "EventKeyboard.h"
#include "Vector.h"
#include "Color.h"
#include "Vector.h"
#include "ResourceManager.h"


TestObject::TestObject() {

	setVelocity(df::Vector(0.1, 0));
	setPosition(df::Vector(5, 5));
	setType("testObject");
	setBox(df::Box(df::Vector(0, 0), 0, 0));
	setSprite("good");
}

int TestObject::eventHandler(const df::Event* p_e)
{
	if (p_e->getType() == "df::mouse") {
		setVelocity(df::Vector(0.3, -0.1));
		return 0;
	}
	else if (p_e->getType() == "df::keyboard") {
		hanndleKeyboard((df::EventKeyboard *)p_e);
		//RM.getSound("good2")->play();
		return 0;
	}
	else if (p_e->getType() == "df::out") {
		setPosition(df::Vector(10,10));
	}
	return -1;
}

int TestObject::getId() const
{
	return Object::getId();
}


void TestObject::hanndleKeyboard(df::EventKeyboard* ev)
{
	if (ev->getKeyboardAction() == df::EventKeyboardAction::KEY_PRESSED) {
		if (ev->getKey() == df::Keyboard::UPARROW) {
			setVelocity(df::Vector(0.0, -0.1));
		}
		else if (ev->getKey() == df::Keyboard::DOWNARROW) {
			setVelocity(df::Vector(0.0, 0.1));
		}
		else if (ev->getKey() == df::Keyboard::LEFTARROW) {
			setVelocity(df::Vector(-0.1, 0.0));
		}
		else if (ev->getKey() == df::Keyboard::RIGHTARROW) {
			setVelocity(df::Vector(0.1, 0.0));
		}
		else if (ev->getKey() == df::Keyboard::Q) {
			GM.setGameOver();
		}
	}
}
