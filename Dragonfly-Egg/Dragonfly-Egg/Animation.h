#pragma once

#include <string>
#include "Sprite.h"

namespace df {
	class Animation {
	private:
		Sprite* m_p_sprite;
		std::string m_name;
		int m_index;
		int m_slowdown_count;

	public:
		Animation();

		void setSprite(Sprite* p_new_sprite);

		Sprite* getSprite() const;

		void setName(std::string new_name);

		std::string getName() const;

		void setIndex(int new_index);

		int getIndex() const;

		void setSlowdownCount(int new_slowdown_count);

		int getSlowdownCount() const;

		int draw(Vector position);
	};
}

