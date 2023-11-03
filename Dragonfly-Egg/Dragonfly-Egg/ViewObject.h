#pragma once

#include <string>

#include "Object.h"
#include "Event.h"

namespace df {
	enum ViewObjectLocation {
		TOP_LEFT, TOP_CENTER, TOP_RIGHT,
		CENTER_LEFT, CENTER_CENTER, CENTER_RIGHT,
		BOTTOM_LEFT, BOTTOM_CENTER, BOTTOM_RIGHT,
	};

	class ViewObject : public Object {
	private:
		std::string m_view_string;
		int m_value;
		bool m_border;
		bool m_draw_value;
		Color m_color;
		ViewObjectLocation location;
	public:
		ViewObject();
		
		virtual int draw();

		virtual int eventHandler(const Event* p_e);

		void setLocation(ViewObjectLocation new_location);

		void setValue(int new_value);

		int getValue() const;

		void setBorder(bool new_border);

		bool getBorder();

		void setColor(Color new_color);

		Color getColor() const;

		void setViewString(std::string new_view_string);

		std::string getViewString() const;

		void setDrawValue(bool new_draw_value = true);

		bool getDrawValue() const;

	};
}
