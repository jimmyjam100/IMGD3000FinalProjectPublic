#pragma once
#include <string>

#include "Frame.h"

namespace df {
	class Sprite {
	private:
		int m_width; // width of sprite
		int m_height; // height of sprite
		int m_max_frame_count; // max number of frames sprite can have
		int m_frame_count; // actual number frames sprite has
		Color m_color; // optional color for entire sprite
		int m_slowdown; // animation slowdown (1=no slowdow, 0=stop)
		Frame* m_frame; // Array of frames
		std::string m_label; // text label to identify sprite.
		Sprite(); // sprite always has one arg, the frame count
	public:
		~Sprite(); // destroy all frames
		
		Sprite(int max_frames); // create sprite with indicated maximum number of frames

		void setWidth(int new_width); // set width of sprite

		int getWidth() const; // get width of sprite

		void setHeight(int new_height); // set height of sprite

		int getHeight() const; // get height of sprite

		void setColor(Color new_color); // sets the color of the sprite

		Color getColor() const; // gets the color of the sprite;

		int getFrameCount() const; // get total count of frames in sprite

		int addFrame(Frame new_frame); //Add frame to sprite. return -1 if frame array full, else 0.

		Frame getFrame(int frame_number) const; //get next sprite frame indicated by number. return empty frame if out of range

		void setLabel(std::string new_label); // set label associated with sprite

		std::string getLabel() const; // Get label associated with sprite

		void setSlowdown(int new_sprite_slowdown); //sets new slowdown

		int getSlowdown() const; // get slowdown number

		int draw(int frame_number, Vector position) const; // draw frame
	};
}
