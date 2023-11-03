#include "GameWin.h"
#include "DisplayManager.h"
#include "WorldManager.h"

GameWin::GameWin(int winning_player)
{
	setType("gamewin");
	top_text = new Object();
	if (winning_player == 1) {
		top_text->setSprite("player1text");
	}
	else {
		top_text->setSprite("player2text");
	}
	top_text->setPosition(df::Vector(DM.getHorizontal() / 2, DM.getVertical() / 2 - 4));
	bottom_text = new Object();
	bottom_text->setSprite("playerwinstext");
	bottom_text->setPosition(df::Vector(DM.getHorizontal() / 2, DM.getVertical() / 2 + 4));


}

GameWin::~GameWin()
{
	WM.markForDelete(top_text);
	WM.markForDelete(bottom_text);
}
