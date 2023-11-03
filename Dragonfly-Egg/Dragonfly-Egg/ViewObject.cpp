#include "ViewObject.h"
#include "WorldManager.h"
#include "DisplayManager.h"
#include <sstream>
#include "EventView.h"

namespace df {
	Vector viewToWorld(Vector view_pos) {
		df::Vector view_origin = WM.getView().getCorner();
		int view_x = view_origin.getX();
		int view_y = view_origin.getY();
		df::Vector world_pos(view_pos.getX() + view_x, view_pos.getY() + view_y);
		return view_pos;
	}

	std::string toString(int i) {
		std::stringstream ss;
		ss << i;
		return ss.str();
	}

	ViewObject::ViewObject()
	{
		setSolidness(Solidness::SPECRAL);
		setAltitude(MAX_ALTITUDE);
		setType("ViewObject");

		setValue(0);
		setDrawValue();
		setBorder(true);
		setLocation(TOP_CENTER);
		setColor(UNDEFINED_COLOR);
	}
	int ViewObject::draw()
	{
		std::string temp_str = "";
		if (m_border) {
			temp_str = " " + getViewString() + " " + toString(m_value) + " ";
		}
		else {
			temp_str = getViewString() + " " + toString(m_value);
		}
		Vector pos = viewToWorld(getPosition());
		DM.drawString(pos, temp_str, getColor());

		return 0;
	}
	int ViewObject::eventHandler(const Event* p_e)
	{
		if (p_e->getType() == VIEW_EVENT) {
			const EventView* p_ve = static_cast<const EventView*> (p_e);
			if (p_ve->getTag() == getViewString()) {
				if (p_ve->getDelta()) {
					setValue(getValue() + p_ve->getValue());
				}
				else {
					setValue(p_ve->getValue());
				}
			}
			return 1;
		}
		return 0;
	}
	void ViewObject::setLocation(ViewObjectLocation new_location)
	{
		float y_delta = 0;
		switch (new_location)
		{
		case df::TOP_LEFT:
			setPosition(Vector(WM.getView().getHorizontal() * 1 / 6, 1));
			if (getBorder() == false) {
				y_delta = -1;
			}
			break;
		case df::TOP_CENTER:
			setPosition(Vector(WM.getView().getHorizontal() * 3 / 6, 1));
			if (getBorder() == false) {
				y_delta = -1;
			}
			break;
		case df::TOP_RIGHT:
			setPosition(Vector(WM.getView().getHorizontal() * 5 / 6, 1));
			if (getBorder() == false) {
				y_delta = -1;
			}
			break;
		case df::CENTER_LEFT:
			setPosition(Vector(WM.getView().getHorizontal() * 1 / 6, WM.getView().getVertical() *3/6));
			if (getBorder() == false) {
				y_delta = -1;
			}
			break;
		case df::CENTER_CENTER:
			setPosition(Vector(WM.getView().getHorizontal() * 3 / 6, WM.getView().getVertical() * 3 / 6));
			if (getBorder() == false) {
				y_delta = -1;
			}
			break;
		case df::CENTER_RIGHT:
			setPosition(Vector(WM.getView().getHorizontal() * 5 / 6, WM.getView().getVertical() * 3 / 6));
			if (getBorder() == false) {
				y_delta = -1;
			}
			break;
		case df::BOTTOM_LEFT:
			setPosition(Vector(WM.getView().getHorizontal() * 1 / 6, WM.getView().getVertical() * 5 / 6));
			if (getBorder() == false) {
				y_delta = -1;
			}
			break;
		case df::BOTTOM_CENTER:
			setPosition(Vector(WM.getView().getHorizontal() * 3 / 6, WM.getView().getVertical() * 5 / 6));
			if (getBorder() == false) {
				y_delta = -1;
			}
			break;
		case df::BOTTOM_RIGHT:
			setPosition(Vector(WM.getView().getHorizontal() * 5 / 6, WM.getView().getVertical() * 5 / 6));
			if (getBorder() == false) {
				y_delta = -1;
			}
			break;
		default:
			break;
		}
		setPosition(Vector(getPosition().getX(), getPosition().getY() + y_delta));

		location = new_location;
	}
	void ViewObject::setValue(int new_value)
	{
		m_value = new_value;
	}
	int ViewObject::getValue() const
	{
		return m_value;
	}
	void ViewObject::setBorder(bool new_border)
	{
		if (m_border != new_border) {
			m_border = new_border;
			setLocation(location);
		}
	}
	bool ViewObject::getBorder()
	{
		return m_border;
	}
	void ViewObject::setColor(Color new_color)
	{
		m_color = new_color;
	}
	Color ViewObject::getColor() const
	{
		return m_color;
	}
	void ViewObject::setViewString(std::string new_view_string)
	{
		m_view_string = new_view_string;
	}
	std::string ViewObject::getViewString() const
	{
		return m_view_string;
	}
	void ViewObject::setDrawValue(bool new_draw_value)
	{
		m_draw_value = new_draw_value;
	}
	bool ViewObject::getDrawValue() const
	{
		return m_draw_value;
	}
}

