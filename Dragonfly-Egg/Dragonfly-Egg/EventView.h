#pragma once
#include "Event.h"

const std::string VIEW_EVENT = "df::view";

namespace df {
	class EventView : public Event {
	private:
		std::string m_tag;
		int m_value;
		bool m_delta;

	public:
		EventView();

		EventView(std::string new_tag, int new_value, bool new_delta);

		void setTag(std::string new_tag);

		std::string getTag() const;

		void setValue(int new_value);

		int getValue() const;

		void setDelta(bool new_delta);

		bool getDelta() const;
	};
}

