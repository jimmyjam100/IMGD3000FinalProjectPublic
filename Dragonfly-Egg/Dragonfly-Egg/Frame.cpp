#include "Frame.h"
#include "DisplayManager.h"

namespace df {
	Frame::Frame()
	{
		m_height = 0;
		m_width = 0;
		m_frame_str = "";
	}
	Frame::Frame(int new_width, int new_height, std::string frame_str)
	{
		m_height = new_height;
		m_width = new_width;
		m_frame_str = frame_str;
	}
	void Frame::setWidth(int new_width)
	{
		m_width = new_width;
	}
	int Frame::getWidth() const
	{
		return m_width;
	}
	void Frame::setHeight(int new_height)
	{
		m_height = new_height;
	}
	int Frame::getHeight() const
	{
		return m_height;
	}
	void Frame::setString(std::string new_frame_str)
	{
		m_frame_str = new_frame_str;
	}
	std::string Frame::getString() const
	{
		return m_frame_str;
	}
	int Frame::draw(Vector position, Color color) const
	{
		if (m_frame_str.empty()) {
			return -1;
		}
		float x_offset = getWidth() / 2;
		float y_offset = getHeight() / 2;
		for (int i = 0; i < m_height; i++) {
			for (int j = 0; j < m_width; j++) {
				Vector tmp = Vector(position.getX() + j - x_offset, position.getY() + i - y_offset);
				DM.drawCh(tmp, m_frame_str[i * m_width + j], color);
			}
		}

		return 0;
	}
}
