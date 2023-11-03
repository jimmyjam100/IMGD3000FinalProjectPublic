#pragma once
#include "Event.h"
#include "Vector.h"

const std::string MSE_EVENT = "df::mouse";

namespace df {
	enum EventMouseAction { // types of mouse actions
		UNDEFINED_MOUSE_ACTION = -1,
		CLICKED,
		PRESSED,
		MOVED,
	};

	namespace Mouse {
		enum Button { // types of mouse buttons
			UNDEFINED_MOUSE_BUTTON = -1,
			LEFT,
			RIGHT,
			MIDDLE,

		};
	}

	class EventMouse : public Event {
	private:
		EventMouseAction m_mouse_action; // Mouse action.
		Mouse::Button m_mouse_button; // Mouse button.
		Vector m_mouse_xy; // Mouse (x,y) coordinates.
	
	public:
		EventMouse(); // create new mouse event
		
		void setMouseAction(EventMouseAction new_mouse_action); // set the action
		
		EventMouseAction getMouseAction() const; // get the action

		void setMouseButton(Mouse::Button new_mouse_button); // set the button

		Mouse::Button getMouseButton() const; // get the button

		void setMousePosition(Vector new_mouse_xy); // set the current mouse position

		Vector getMousePosition() const; // get the current mouse position
	};
}

