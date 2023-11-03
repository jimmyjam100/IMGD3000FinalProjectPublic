#include "Star.h"
#include "DisplayManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"

Star::Star()
{
	setStartPosition();
	setType("Star");
	setSprite("star");
	setSolidness(df::SOFT);
	//setSprite("good");
}

int Star::draw()
{
	if (m_twinkle_counter == 0) {
		if (rand() % 500 == 1) {
			m_twinkle_counter = 10;
		}
		Object::draw();
	}
	else {
		--m_twinkle_counter;
		DM.drawCh(getPosition(), '*', df::WHITE);
	}


	return 0;
}

void Star::setStartPosition()
{
	// 0 to 79 in x, 2 to 20 in y
	bool blocking = true;
	df::Vector v;
	while (blocking) {
		blocking = false;
		v = df::Vector(rand() % 80, rand() % 18 + 2);
		if ((v.getX() > 25 && v.getX() < 55) && (v.getY() > 3 && v.getY() < 18)) {
			blocking = true;
		}
	}
	setPosition(v);
}