#pragma once
#include "Event.h"

const std::string KEYBOARD_EVENT = "df::keyboard";
namespace df {
	enum EventKeyboardAction { // different types of keyboard actions
		UNDEFINED_KEYBOARD_ACTION = -1,
		KEY_PRESSED,
		KEY_RELEASED,
		KEY_DOWN,
	};
	namespace Keyboard { // different type of keys
		enum Key {
			UNDEFINED_KEY = -1,
			SPACE, RETURN, ESCAPE, TAB, LEFTARROW, RIGHTARROW, UPARROW, DOWNARROW,
			PAUSE, MINUS, PLUS, TILDE, PERIOD, COMMA, SLASH, LEFTCONTROL,
			RIGHTCONTROL, LEFTSHIFT, RIGHTSHIFT, F1, F2, F3, F4, F5, F6, F7, F8,
			F9, F10, F11, F12, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q,
			R, S, T, U, V, W, X, Y, Z, NUM1, NUM2, NUM3, NUM4, NUM5, NUM6, NUM7,
			NUM8, NUM9, NUM0,
		};
	}

	class EventKeyboard : public Event {
	private:
		Keyboard::Key m_key_val; // the key that did the action
		EventKeyboardAction m_keyboard_action; // the action that happened
	public:
		EventKeyboard(); //create a new keyboard event

		void setKey(Keyboard::Key new_key); //set the key in the event

		Keyboard::Key getKey() const; //get the key in the event

		void setKeyboardAction(EventKeyboardAction new_action); // set action

		EventKeyboardAction getKeyboardAction() const; // get action
	};
}
