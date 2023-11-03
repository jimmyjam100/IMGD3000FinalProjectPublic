#pragma once
#ifndef __EVENT_H__
#define __EVENT_H__
#include <string>

const std::string UNDEFINED_EVENT = "df::undefined";
namespace df {
	class Event {
	private:
		std::string m_event_type; // the type of event

	public:
		Event(); // construct the event
		virtual ~Event(); // deletes the event
		void setType(std::string new_type); //changes the type of the event
		std::string getType() const; // gets the type of the event
	};
}

#endif