#pragma once
#include "Event.h"
#include "Object.h"
#ifndef __EVENTCOLLISION_H__
#define __EVENTCOLLISION_H__
const std::string COLLISION_EVENT = "df::collision";

namespace df {
	class EventCollision : public Event {
	private:
		Vector m_pos; //where the collision occurred
		Object* m_p_obj1; //object moving
		Object* m_p_obj2; //other object

	public:
		EventCollision(); //creates collision event

		EventCollision(Object* p_o1, Object* p_o2, Vector p); //collision with paramaters

		void setObject1(Object* p_new_o1); // set object 1

		Object* getObject1() const; //get object 1

		void setObject2(Object* p_new_o2); // set object 2

		Object* getObject2() const; //get object 2

		void setPosition(Vector new_pos); //set position of colllision

		Vector getPosition() const; //get position of collision
	};
}




#endif // !__EVENTCOLLISION_H__

