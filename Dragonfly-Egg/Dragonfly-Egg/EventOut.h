#pragma once
#ifndef __EVENTOUT_H__
#define __EVENTOUT_H__

#include "Event.h"

const std::string OUT_EVENT = "df::out";

namespace df {
	class EventOut : public Event {
	public:
		EventOut(); // constructor
	};
}



#endif