#include "Floor.h"
#include "WorldManager.h"
Floor::Floor()
{
	setSprite("floor");
	setSolidness(df::SPECRAL);
	setPosition(df::Vector(WM.getBoundary().getHorizontal()/2, WM.getBoundary().getVertical() - 2));
}
