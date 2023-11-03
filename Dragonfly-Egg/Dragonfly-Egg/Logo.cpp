#include "Logo.h"
#include "WorldManager.h"
#include "DisplayManager.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include <time.h>

void Logo::startGame()
{
	if (!isStarted) {
		srand(time(NULL));
		int music_num = rand() % 3;
		RM.getMusic(music_playing)->stop();
		switch (music_num)
		{
		case 0:
			RM.getMusic("BDMainTheme")->play();
			music_playing = "BDMainTheme";
			break;
		case 1:
			RM.getMusic("BDResurrection")->play();
			music_playing = "BDResurrection";
			break;
		case 2:
			RM.getMusic("BDPowerCore")->play();
			music_playing = "BDPowerCore";
			break;
		default:
			break;
		}
		p1 = new Player(false, this);
		p2 = new Player(true, this);
		setSprite("star");
		setPosition(df::Vector(-1, -1));
		isStarted = true;
	}
}

void Logo::endGame()
{
	if (isStarted) {
		WM.markForDelete(p1);
		WM.markForDelete(p2);
		std::vector<Object*> allObjs = WM.getAllObjects();
		std::vector<Object*>::iterator it = allObjs.begin();
		while (it != allObjs.end()) {
			if ((*it)->getType() == "gamewin") {
				WM.markForDelete(*it);
				break;
			}
			++it;
		}
		p1 = NULL;
		p2 = NULL;
		setSprite("logo");
		setPosition(df::Vector(DM.getHorizontal() / 2, DM.getVertical() / 2));
		isStarted = false;
	}

}

Logo::Logo() {
	setSprite("logo");
	setPosition(df::Vector(DM.getHorizontal()/2, DM.getVertical()/2));
	isStarted = false;
	p1 = NULL;
	p2 = NULL;
	held = false;
	nextHeld = false;
	srand(time(NULL));
	int music_num = rand() % 3;
	switch (music_num)
	{
	case 0:
		RM.getMusic("BDMainTheme")->play();
		music_playing = "BDMainTheme";
		break;
	case 1:
		RM.getMusic("BDResurrection")->play();
		music_playing = "BDResurrection";
		break;
	case 2:
		RM.getMusic("BDPowerCore")->play();
		music_playing = "BDPowerCore";
		break;
	default:
		break;
	}
}

int Logo::eventHandler(const df::Event* p_e)
{
	if (p_e->getType() == "df::gamepad") {
		const df::EventGamepad* e = dynamic_cast<const df::EventGamepad*>(p_e);
		hanndleGamepad(e);
	}
	else if (p_e->getType() == "df::step") {
		held = nextHeld;
		nextHeld = false;
	}
	return 0;
}

void Logo::hanndleGamepad(const df::EventGamepad *e)
{
	if (e->getButton() == df::Gamepad::Start1 || e->getButton() == df::Gamepad::Start2) {
		if (!held) {
			if (isStarted) {
				endGame();

			}
			else {
				startGame();
			}
		}
		nextHeld = true;
	}
	else if ((e->getButton() == df::Gamepad::Select1 || e->getButton() == df::Gamepad::Select2) && !isStarted) {
		GM.setGameOver();
	}
}
