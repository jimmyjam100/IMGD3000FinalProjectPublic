#include "Object.h"
#include "WorldManager.h"
#include "LogManager.h"
#include "ResourceManager.h"

namespace df {

	Object::Object(){
		static int single = 0;
		m_id = single;
		++single;
		m_position = Vector(0, 0);
		m_type = "Untyped Object";
		m_altitude = 0;
		m_solidness = HARD;
		WM.insertObject(this);
		m_animation = Animation();
		m_box = Box();
	}

	Object::~Object(){
		LM.writeLog("Deleteing Object");
		WM.removeObject(this);
	}

	void Object::setId(int new_id){
		m_id = new_id;
		LM.writeLog("Set ID for Object");
	}

	int Object::getId() const
	{
		return m_id;
	}

	void Object::setType(std::string new_type)
	{
		LM.writeLog("Set Object Type");
		m_type = new_type;
	}

	std::string Object::getType() const
	{
		return m_type;
	}

	void Object::setPosition(Vector new_pos)
	{
		LM.writeLog("Set Object Position");
		m_position = new_pos;
	}

	Vector Object::getPosition() const
	{
		return m_position;
	}

	int Object::eventHandler(const Event* p_e){
		return -1;
	}

	int Object::draw()
	{
		if (m_animation.getSprite() != NULL) {
			m_animation.draw(m_position);
		}
		return -1;
	}

	int Object::getAltitude() const
	{
		return m_altitude;
	}

	int Object::setAltitude(int a)
	{
		if (a > MAX_ALTITUDE || a < 0) {
			return -1;
		}
		m_altitude = a;
		return 0;
	}

	void Object::setSpeed(float speed)
	{
		m_speed = speed;
	}

	float Object::getSpeed() const
	{
		return m_speed;
	}

	void Object::setDirection(Vector new_direction)
	{
		m_direction = new_direction;
	}

	Vector Object::getDirection() const
	{
		return m_direction;
	}

	void Object::setVelocity(Vector new_velocity)
	{
		m_speed = new_velocity.getMagnitude();
		m_direction = new_velocity;
		m_direction.normalize();
	}

	Vector Object::getXVelocity() const
	{
		return Vector(m_direction.getX()*m_speed, 0);
	}

	Vector Object::getYVelocity() const
	{
		return Vector(0, m_direction.getY() * m_speed);
	}

	Vector Object::predictPosition() const
	{
		return Vector(m_position.getX() + m_direction.getX() * m_speed, m_position.getY() + m_direction.getY() * m_speed);
	}

	bool Object::isSolid() const
	{
		return !(m_solidness == SPECRAL);
	}

	int Object::setSolidness(Solidness new_solid)
	{
		m_solidness = new_solid;
		return 0;
	}

	Solidness Object::getSolidness() const
	{
		return m_solidness;
	}

	int Object::setSprite(std::string sprite_label)
	{
		Animation a = Animation();
		Sprite* s = RM.getSprite(sprite_label);
		if (s == NULL) {
			return -1;
		}
		a.setSprite(s);
		m_animation = a;
		m_box.setHorizontal(s->getWidth());
		m_box.setVertical(s->getHeight());
		return 0;
	}

	void Object::setAnimation(Animation new_animation)
	{
		m_animation = new_animation;
	}

	Animation Object::getAnimation() const
	{
		return m_animation;
	}

	void Object::setBox(Box new_box)
	{
		m_box = new_box;
	}

	Box Object::getBox() const
	{
		return m_box;
	}

}


