#include "InputManager.h"
#include "DisplayManager.h"
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "GameManager.h"
#include "EventGamepad.h"
#include "LogManager.h"

df::Keyboard::Key getKey(sf::Keyboard::Key j) {
	switch (j) {
	case sf::Keyboard::A:
		return df::Keyboard::A;
	case sf::Keyboard::B:
		return df::Keyboard::B;
	case sf::Keyboard::C:
		return df::Keyboard::C;
	case sf::Keyboard::D:
		return df::Keyboard::D;
	case sf::Keyboard::E:
		return df::Keyboard::E;
	case sf::Keyboard::F:
		return df::Keyboard::F;
	case sf::Keyboard::G:
		return df::Keyboard::G;
	case sf::Keyboard::H:
		return df::Keyboard::H;
	case sf::Keyboard::I:
		return df::Keyboard::I;
	case sf::Keyboard::J:
		return df::Keyboard::J;
	case sf::Keyboard::K:
		return df::Keyboard::K;
	case sf::Keyboard::L:
		return df::Keyboard::L;
	case sf::Keyboard::M:
		return df::Keyboard::M;
	case sf::Keyboard::N:
		return df::Keyboard::N;
	case sf::Keyboard::O:
		return df::Keyboard::O;
	case sf::Keyboard::P:
		return df::Keyboard::P;
	case sf::Keyboard::Q:
		return df::Keyboard::Q;
	case sf::Keyboard::R:
		return df::Keyboard::R;
	case sf::Keyboard::S:
		return df::Keyboard::S;
	case sf::Keyboard::T:
		return df::Keyboard::T;
	case sf::Keyboard::U:
		return df::Keyboard::U;
	case sf::Keyboard::V:
		return df::Keyboard::V;
	case sf::Keyboard::W:
		return df::Keyboard::W;
	case sf::Keyboard::X:
		return df::Keyboard::X;
	case sf::Keyboard::Y:
		return df::Keyboard::Y;
	case sf::Keyboard::Z:
		return df::Keyboard::Z;
	case sf::Keyboard::Comma:
		return df::Keyboard::COMMA;
	case sf::Keyboard::Down:
		return df::Keyboard::DOWNARROW;
	case sf::Keyboard::Escape:
		return df::Keyboard::ESCAPE;
	case sf::Keyboard::F1:
		return df::Keyboard::F1;
	case sf::Keyboard::F2:
		return df::Keyboard::F2;
	case sf::Keyboard::F3:
		return df::Keyboard::F3;
	case sf::Keyboard::F4:
		return df::Keyboard::F4;
	case sf::Keyboard::F5:
		return df::Keyboard::F5;
	case sf::Keyboard::F6:
		return df::Keyboard::F6;
	case sf::Keyboard::F7:
		return df::Keyboard::F7;
	case sf::Keyboard::F8:
		return df::Keyboard::F8;
	case sf::Keyboard::F9:
		return df::Keyboard::F9;
	case sf::Keyboard::F10:
		return df::Keyboard::F10;
	case sf::Keyboard::F11:
		return df::Keyboard::F11;
	case sf::Keyboard::F12:
		return df::Keyboard::F12;
	case sf::Keyboard::Left:
		return df::Keyboard::LEFTARROW;
	case sf::Keyboard::LControl:
		return df::Keyboard::LEFTCONTROL;
	case sf::Keyboard::LShift:
		return df::Keyboard::LEFTSHIFT;
	case sf::Keyboard::Hyphen:
		return df::Keyboard::MINUS;
	case sf::Keyboard::Num0:
		return df::Keyboard::NUM0;
	case sf::Keyboard::Num1:
		return df::Keyboard::NUM1;
	case sf::Keyboard::Num2:
		return df::Keyboard::NUM2;
	case sf::Keyboard::Num3:
		return df::Keyboard::NUM3;
	case sf::Keyboard::Num4:
		return df::Keyboard::NUM4;
	case sf::Keyboard::Num5:
		return df::Keyboard::NUM5;
	case sf::Keyboard::Num6:
		return df::Keyboard::NUM6;
	case sf::Keyboard::Num7:
		return df::Keyboard::NUM7;
	case sf::Keyboard::Num8:
		return df::Keyboard::NUM8;
	case sf::Keyboard::Num9:
		return df::Keyboard::NUM9;
	case sf::Keyboard::Pause:
		return df::Keyboard::PAUSE;
	case sf::Keyboard::Period:
		return df::Keyboard::PERIOD;
	case sf::Keyboard::Add:
		return df::Keyboard::PLUS;
	case sf::Keyboard::Return:
		return df::Keyboard::RETURN;
	case sf::Keyboard::Right:
		return df::Keyboard::RIGHTARROW;
	case sf::Keyboard::RControl:
		return df::Keyboard::RIGHTCONTROL;
	case sf::Keyboard::RShift:
		return df::Keyboard::RIGHTSHIFT;
	case sf::Keyboard::Slash:
		return df::Keyboard::SLASH;
	case sf::Keyboard::Space:
		return df::Keyboard::SPACE;
	case sf::Keyboard::Tab:
		return df::Keyboard::TAB;
	case sf::Keyboard::Tilde:
		return df::Keyboard::TILDE;
	case sf::Keyboard::Up:
		return df::Keyboard::UPARROW;
	default:
		return df::Keyboard::UNDEFINED_KEY;
	}
}

namespace df {
	InputManager::InputManager() {

	}

	void InputManager::operator=(InputManager const&)
	{
	}
	InputManager& InputManager::getInstance()
	{
		static InputManager single;
		return single;
	}
	int InputManager::startUp()
	{
		if (!DM.isStarted()) {
			return -1;
		}
		sf::RenderWindow *window = DM.getWindow();
		window->setKeyRepeatEnabled(false);
		return Manager::startUp();
	}
	void InputManager::shutDown()
	{
		if (!DM.isStarted()) {
			Manager::shutDown();
			return;
		}
		sf::RenderWindow* window = DM.getWindow();
		window->setKeyRepeatEnabled(true);
		Manager::shutDown();
	}
	void InputManager::getInput()
	{
		sf::Event event;
		while (DM.getWindow()->pollEvent(event)) {
			if (event.type == sf::Event::KeyPressed) {
				EventKeyboard* ev = new EventKeyboard();
				ev->setKey(getKey(event.key.code));
				ev->setKeyboardAction(EventKeyboardAction::KEY_DOWN);
				GM.onEvent(ev);
				delete ev;

			}
			if (event.type == sf::Event::KeyReleased) {
				EventKeyboard* ev = new EventKeyboard();
				ev->setKey(getKey(event.key.code));
				ev->setKeyboardAction(EventKeyboardAction::KEY_RELEASED);
				GM.onEvent(ev);
				delete ev;
			}
			if (event.type == sf::Event::MouseMoved) {
				EventMouse* ev = new EventMouse();
				ev->setMouseButton(Mouse::LEFT);
				ev->setMouseAction(EventMouseAction::MOVED);
				ev->setMousePosition(Vector(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y));
				GM.onEvent(ev);
				delete ev;
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Right) {
					EventMouse* ev = new EventMouse();
					ev->setMouseButton(Mouse::RIGHT);
					ev->setMouseAction(EventMouseAction::CLICKED);
					ev->setMousePosition(Vector(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y));
					GM.onEvent(ev);
					delete ev;
				}
				else {
					EventMouse* ev = new EventMouse();
					ev->setMouseButton(Mouse::LEFT);
					ev->setMouseAction(EventMouseAction::CLICKED);
					ev->setMousePosition(Vector(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y));
					GM.onEvent(ev);
					delete ev;
				}
			}
		}
		for (int i = 0; i < sf::Keyboard::KeyCount; i++) {
			sf::Keyboard::Key j = (sf::Keyboard::Key) i;
			if (sf::Keyboard::isKeyPressed(j)) {
				EventKeyboard* ev = new EventKeyboard();
				ev->setKey(getKey(j));
				ev->setKeyboardAction(EventKeyboardAction::KEY_PRESSED);
				GM.onEvent(ev);
				delete ev;
			}
		}
		if (sf::Joystick::isConnected(0))
		{
			float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
			float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
			if (x < -40) {
				EventGamepad e = EventGamepad();
				e.setButton(df::Gamepad::Left1);
				GM.onEvent(&e);
			}
			else if (x > 40) {
				EventGamepad e = EventGamepad();
				e.setButton(df::Gamepad::Right1);
				GM.onEvent(&e);
			}
			if (y < -40) {
				EventGamepad e = EventGamepad();
				e.setButton(df::Gamepad::Up1);
				GM.onEvent(&e);
			}
			else if (y > 40) {
				EventGamepad e = EventGamepad();
				e.setButton(df::Gamepad::Down1);
				GM.onEvent(&e);
			}

			for (int i = 0; i < 10; ++i) {
				if (sf::Joystick::isButtonPressed(0, i))
				{
					EventGamepad e = EventGamepad();
					switch (i) {
					case 0:
						e.setButton(df::Gamepad::A1);
						break;
					case 1:
						e.setButton(df::Gamepad::B1);
						break;
					case 2:
						e.setButton(df::Gamepad::X1);
						break;
					case 3:
						e.setButton(df::Gamepad::Y1);
						break;
					case 4:
						LM.writeLog("button4Pressed"); // left bumper
						break;
					case 5:
						LM.writeLog("button5Pressed"); // right bumper
						break;
					case 6:
						e.setButton(df::Gamepad::Select1);
						break;
					case 7:
						e.setButton(df::Gamepad::Start1);
						break;
					case 8:
						LM.writeLog("button8Pressed");
						break;
					case 9:
						LM.writeLog("button9Pressed");
						break;
					case 10:
						LM.writeLog("button10Pressed");
						break;
					}
					GM.onEvent(&e);
				}
			}
		}
		if (sf::Joystick::isConnected(1))
		{
			float x = sf::Joystick::getAxisPosition(1, sf::Joystick::X);
			float y = sf::Joystick::getAxisPosition(1, sf::Joystick::Y);
			if (x < -40) {
				EventGamepad e = EventGamepad();
				e.setButton(df::Gamepad::Left2);
				GM.onEvent(&e);
			}
			else if (x > 40) {
				EventGamepad e = EventGamepad();
				e.setButton(df::Gamepad::Right2);
				GM.onEvent(&e);
			}
			if (y < -40) {
				EventGamepad e = EventGamepad();
				e.setButton(df::Gamepad::Up2);
				GM.onEvent(&e);
			}
			else if (y > 40) {
				EventGamepad e = EventGamepad();
				e.setButton(df::Gamepad::Down2);
				GM.onEvent(&e);
			}

			for (int i = 0; i < 10; ++i) {
				if (sf::Joystick::isButtonPressed(1, i))
				{
					EventGamepad e = EventGamepad();
					switch (i) {
					case 0:
						e.setButton(df::Gamepad::A2);
						break;
					case 1:
						e.setButton(df::Gamepad::B2);
						break;
					case 2:
						e.setButton(df::Gamepad::X2);
						break;
					case 3:
						e.setButton(df::Gamepad::Y2);
						break;
					case 6:
						e.setButton(df::Gamepad::Select2);
						break;
					case 7:
						e.setButton(df::Gamepad::Start2);
						break;
					}
					GM.onEvent(&e);
				}
			}
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			EventMouse* ev = new EventMouse();
			ev->setMouseButton(Mouse::LEFT);
			ev->setMouseAction(EventMouseAction::PRESSED);
			ev->setMousePosition(Vector(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y));
			GM.onEvent(ev);
			delete ev;

		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			EventMouse* ev = new EventMouse();
			ev->setMouseButton(Mouse::RIGHT);
			ev->setMouseAction(EventMouseAction::PRESSED);
			ev->setMousePosition(Vector(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y));
			GM.onEvent(ev);
			delete ev;

		}
	}

	
}


