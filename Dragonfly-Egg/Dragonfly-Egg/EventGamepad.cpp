#include "EventGamepad.h"


namespace df {
	EventGamepad::EventGamepad()
	{
		setType(GAMEPAD_EVENT);
		m_button_val = Gamepad::UNDEFINED_KEY;
	}

	void EventGamepad::setButton(Gamepad::Button new_gamepad)
	{
		m_button_val = new_gamepad;
	}

	Gamepad::Button EventGamepad::getButton() const
	{
		return m_button_val;
	}
}

