#pragma once
#include "Event.h"

const std::string GAMEPAD_EVENT = "df::gamepad";
namespace df {
	namespace Gamepad { // different type of keys
		enum Button {
			UNDEFINED_KEY = -1,
			Left1, Right1, Down1, Up1, A1, B1, X1, Y1, Start1, Select1,
			Left2, Right2, Down2, Up2, A2, B2, X2, Y2, Start2, Select2
		};
	}

	class EventGamepad : public Event {
	private:
		Gamepad::Button m_button_val; // the key that did the action
	public:
		EventGamepad(); //create a new keyboard event

		void setButton(Gamepad::Button new_gamepad); //set the key in the event

		Gamepad::Button getButton() const; //get the key in the event

	};
}