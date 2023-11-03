#pragma once

#include "Vector.h"

namespace df {

	class Box {
	private:
		Vector m_corner;
		float m_horizontal;
		float m_vertical;

	public:
		Box(); // Create box with (0,0) for the corner, and no size

		Box(Vector init_corner, float init_horizontal, float init_vertical); // Create box with an upper left corner, horiz and vert sizes;

		Vector getCorner() const; // Get the corner

		void setCorner(Vector new_corner); //set the corner

		float getHorizontal() const; // get horizonal size of box

		void setHorizontal(float new_horizontal); // set horizontal size of box

		float getVertical() const; // get vertical of box
		
		void setVertical(float new_vertical); // set vertical of box
	};

}