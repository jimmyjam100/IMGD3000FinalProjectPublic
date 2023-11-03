#pragma once
#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "Vector.h"
#include "Event.h"
#include "Animation.h"
#include "Box.h"

const int MAX_ALTITUDE = 4;
namespace df {
	enum Solidness {
		HARD,
		SOFT,
		SPECRAL
	};


	class Object {
	private:
		Solidness m_solidness;
		int m_id;     // Unique game engine defined identifier.
		int m_altitude; // altatude of object
		std::string m_type; //Game programmer defined type
		Vector m_position; // Position in game world
		Vector m_direction; // direction object is moving
		float m_speed; // speed of object
		Animation m_animation; // annimation associated with object
		Box m_box;

	public:
		Object(); // Construct Object. Set default parameters and add to game world
		virtual ~Object(); // destroy object remove from game world
		void setId(int new_id); // sets object Id
		int getId() const; // gets object Id

		void setType(std::string new_type); // sets Type of object

		std::string getType() const; // gets type of the object
		void setPosition(Vector new_pos); // set position of the object

		Vector getPosition() const; //gets position of the object

		virtual int eventHandler(const Event* p_e); //Handle event (default is to ignore everthing) returns 0 if ignored, else 1.

		virtual int draw(); // draw the object

		int getAltitude() const; // get object altitude

		int setAltitude(int a); // set object altitude

		void setSpeed(float speed); // set object speed

		float getSpeed() const; // get object speed

		void setDirection(Vector new_direction); // set object direction

		Vector getDirection() const; // get object direction

		void setVelocity(Vector new_velocity); // set velocity

		Vector getXVelocity() const; // get x velocity

		Vector getYVelocity() const; // get y velocity

		Vector predictPosition() const; // predict position next frame

		bool isSolid() const; // get if object is solid

		int setSolidness(Solidness new_solid); // set objects solid level

		Solidness getSolidness() const; // get objects solid level

		int setSprite(std::string sprite_label); // set the sprite of the object

		void setAnimation(Animation new_animation); // set the animation of the object

		Animation getAnimation() const; // get the animation of the object

		void setBox(Box new_box); // Set object's bounding box

		Box getBox() const; // Get object's bounding box


	};
}
#endif