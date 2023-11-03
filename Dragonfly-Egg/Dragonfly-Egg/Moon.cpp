#include "Moon.h"
#include "WorldManager.h"

Moon::Moon()
{
	setSprite("moon");
	setType("Moon");
	setSolidness(df::HARD);
	setPosition(df::Vector(WM.getBoundary().getHorizontal() / 2, WM.getBoundary().getVertical() - 13));
}
