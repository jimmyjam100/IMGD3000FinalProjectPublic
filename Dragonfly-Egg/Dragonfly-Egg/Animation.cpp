#include "Animation.h"

namespace df {
	Animation::Animation()
	{
		m_index = 0;
		m_name = "";
		m_p_sprite = NULL;
		m_slowdown_count = 1;
	}
	void Animation::setSprite(Sprite* p_new_sprite)
	{
		m_p_sprite = p_new_sprite;
	}
	Sprite* Animation::getSprite() const
	{
		return m_p_sprite;
	}
	void Animation::setName(std::string new_name)
	{
		m_name = new_name;
	}
	std::string Animation::getName() const
	{
		return m_name;
	}
	void Animation::setIndex(int new_index)
	{
		m_index = new_index;
	}
	int Animation::getIndex() const
	{
		return m_index;
	}
	void Animation::setSlowdownCount(int new_slowdown_count)
	{
		m_slowdown_count = new_slowdown_count;
	}
	int Animation::getSlowdownCount() const
	{
		return m_slowdown_count;
	}
	int Animation::draw(Vector position)
	{
		if (m_p_sprite == NULL) {
			return 0;
		}

		m_p_sprite->draw(getIndex(), position);
		if (getSlowdownCount() == -1) {
			return 0;
		}
		setSlowdownCount(getSlowdownCount() + 1);
		if (getSlowdownCount() >= m_p_sprite->getSlowdown()) {
			setSlowdownCount(0);
			++m_index;

			if (m_index >= m_p_sprite->getFrameCount()) {
				m_index = 0;
			}
		}
		return 0;
	}
}

