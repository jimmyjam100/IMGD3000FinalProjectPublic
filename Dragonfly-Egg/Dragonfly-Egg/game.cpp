#define NOMINMAX
#include "LogManager.h"
#include "GameManager.h"
#include "Clock.h"
#include <windows.h>
#include <string>
#include <iostream>
#include <cstring>
#include "Object.h"
#include "WorldManager.h"
#include "DisplayManager.h"
#include "ResourceManager.h"
#include "TestObject.h"
#include "TestObject2.h"
#include "Vector.h"
#include "Star.h"
#include "ViewObject.h"
#include "Player.h"
#include "Floor.h"
#include "Moon.h"

int main(int argc, char* argv[]) {
	GM.startUp();
	int val1 = RM.loadSprite("sprites\\player-spr-fl-2.txt", "leftplayer2");
	int val2 = RM.loadSprite("sprites\\player-spr-fr-2.txt", "rightplayer2");
	int val3 = RM.loadSprite("sprites\\player-spr-fl-1.txt", "leftplayer1");
	int val4 = RM.loadSprite("sprites\\player-spr-fr-1.txt", "rightplayer1");
	int val5 = RM.loadSprite("sprites\\player-spr-fl-hs.txt", "lefthitstun");
	int val6 = RM.loadSprite("sprites\\player-spr-fr-hs.txt", "righthitstun");
	int val7 = RM.loadSprite("sprites\\player-spr-fr-1-taunt.txt", "righttaunt1");
	int val8 = RM.loadSprite("sprites\\player-spr-fl-1-taunt.txt", "lefttaunt1");
	int val9 = RM.loadSprite("sprites\\player-spr-fr-2-taunt.txt", "righttaunt2");
	int val10 = RM.loadSprite("sprites\\player-spr-fl-2-taunt.txt", "lefttaunt2");
	int val11 = RM.loadSprite("sprites\\player-spr-fl-1-shoot.txt", "leftshoot1");
	int val12 = RM.loadSprite("sprites\\player-spr-fl-2-shoot.txt", "leftshoot2");
	int val13 = RM.loadSprite("sprites\\player-spr-fr-1-shoot.txt", "rightshoot1");
	int val14 = RM.loadSprite("sprites\\player-spr-fr-2-shoot.txt", "rightshoot2");
	int val24 = RM.loadSprite("sprites\\logo-spr.txt", "logo");
	int val25 = RM.loadSprite("sprites\\logoBlank-spr.txt", "Blank");
	int val26 = RM.loadSprite("sprites\\player-1-text-spr.txt", "player1text");
	int val27 = RM.loadSprite("sprites\\player-2-text-spr.txt", "player2text");
	int val28 = RM.loadSprite("sprites\\player-wins-text-spr.txt", "playerwinstext");

	int val15 = RM.loadSprite("sprites\\laser-spr.txt", "laser");
	int val16 = RM.loadSprite("sprites\\missile-spr-fl.txt", "leftmissile");
	int val17 = RM.loadSprite("sprites\\missile-spr-fr.txt", "rightmissile");
	int val18 = RM.loadSprite("sprites\\large-shot-spr.txt", "lcs");
	int val19 = RM.loadSprite("sprites\\medium-shot-spr.txt", "mcs");
	int val20 = RM.loadSprite("sprites\\small-shot-spr.txt", "scs");
	int val21 = RM.loadSprite("sprites\\no-shot-spr.txt", "ncs");
	int val22 = RM.loadSprite("sprites\\reflector-spr.txt", "reflector");
	int val23 = RM.loadSprite("sprites\\star-spr.txt", "star");

	//sounds
	RM.loadSound("sprites\\fire.wav", "fireLaser");
	RM.loadSound("sprites\\explode.wav", "hit");
	RM.loadSound("sprites\\shield.wav", "shield");
	RM.loadSound("sprites\\shine.wav", "reflect");
	RM.loadSound("sprites\\chargeshot.wav", "chargeshot");
	RM.loadSound("sprites\\missile.wav", "missile");
	RM.loadSound("sprites\\howl.wav", "howl");
	RM.loadSound("sprites\\reflectmiss.wav", "reflectmiss");
	RM.loadSound("sprites\\deathblast.wav", "deathblast");
	if (RM.loadSprite("sprites\\floor-spr.txt", "floor") == 0) {
		std::cout << "loaded" << std::endl;
	}
	if (RM.loadSprite("sprites\\moon-spr.txt", "moon") == 0) {
		std::cout << "loaded" << std::endl;
	}
	RM.loadSprite("C:\\Users\\jimmyjam100\\source\\repos\\Dragonfly-Egg\\Dragonfly-Egg\\sprites\\bad-spr.txt", "bad");
	RM.loadSound("C:\\Users\\jimmyjam100\\source\\repos\\game0\\sounds\\explode.wav", "good2");

	//music
	RM.loadMusic("sprites\\BDResurrection.wav", "BDResurrection");
	RM.loadMusic("sprites\\BDMainTheme.wav", "BDMainTheme");
	RM.loadMusic("sprites\\BDPowerCore.wav", "BDPowerCore");

	new Moon();
	new Floor();
	new Logo();

	//Player* p1 = new Player(false, );
	//Player* p2 = new Player(true);
	

	for (int i = 0; i < 30; i++) {
		new Star();
	}
	
	//df::Object* obj1 = new TestObject();
	//TestObject2* obj2 = new TestObject2();
	//for (int i = 0; i < 20; i++) {
		//new Star();
	//}
	//df::ViewObject* obj3 = new df::ViewObject();
	//obj3->setViewString("hello");
	//obj3->setColor(df::BLUE);
	//obj3->setLocation(df::CENTER_CENTER);
	//WM.setViewFollowing(obj1);
	//WM.setView(df::Box(df::Vector(0, 0), DM.getHorizontal() * 2, DM.getVertical() * 2));
	//WM.setBoundary(df::Box(df::Vector(0, 0), DM.getHorizontal() * 2, DM.getVertical() * 2));
	GM.run();
	GM.shutDown();
}