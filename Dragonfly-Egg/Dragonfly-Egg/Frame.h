#pragma once
#include <string>
#include "Vector.h"
#include "Color.h"

namespace df {
	class Frame {
	private:
		int m_width;
		int m_height;
		std::string m_frame_str;

	public:
		
		Frame(); //Create an empty frame

		Frame(int new_width, int new_height, std::string frame_str); //create frame with all info

		void setWidth(int new_width); //set width of frame

		int getWidth() const; //get width of frame

		void setHeight(int new_height); //set height of frame

		int getHeight() const; //get height of frame

		void setString(std::string new_frame_str); // set string of frame

		std::string getString() const; // get string of frame

		int draw(Vector position, Color color) const;
	};
}