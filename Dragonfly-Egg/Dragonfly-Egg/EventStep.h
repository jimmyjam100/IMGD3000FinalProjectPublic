#pragma once
#ifndef __EVENTSTEP_H__
#define __EVENTSTEP_H__

#include "Event.h"

const std::string STEP_EVENT = "df::step";

namespace df {
	class EventStep : public Event {
	private:
		int m_step_count; // iteration number of game loop

	public:
		EventStep(); // constructor
		EventStep(int init_step_count); // other constructer
		void setStepCount(int new_step_count); // set step count
		int getStepCount() const; // get step cound
	};
}



#endif