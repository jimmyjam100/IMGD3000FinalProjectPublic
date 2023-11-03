#include "WorldManager.h"
#include "Object.h"
#include "EventStep.h"
#include "LogManager.h"
#include "Vector.h"
#include "EventCollision.h"
#include "DisplayManager.h"
#include "EventOut.h"
#include "ViewObject.h"


namespace df {
	bool boxIntersectsBox(df::Box b1, df::Box b2) {
		if (b1.getCorner().getX() + b1.getHorizontal() > b2.getCorner().getX() &&
			b1.getCorner().getX() < b2.getCorner().getX() + b2.getHorizontal() &&
			b1.getCorner().getY() + b1.getVertical() > b2.getCorner().getY() &&
			b1.getCorner().getY() < b2.getCorner().getY() + b2.getVertical()) {
			return true;
		}
		return false;
	}

	df::Box getWorldBox(const df::Object* p_o) {
		df::Box temp_box = p_o->getBox();
		df::Vector corner = temp_box.getCorner();
		corner.setX(corner.getX() + p_o->getPosition().getX());
		corner.setY(corner.getY() + p_o->getPosition().getY());
		temp_box.setCorner(corner);
		return temp_box;
	}

	df::Box getWorldBoxWithPos(const df::Object* p_o, df::Vector pos) {
		df::Box temp_box = p_o->getBox();
		df::Vector corner = temp_box.getCorner();
		corner.setX(corner.getX() + pos.getX());
		corner.setY(corner.getY() + pos.getY());
		temp_box.setCorner(corner);
		return temp_box;
	}
	void WorldManager::operator=(WorldManager const&) {
		//does not need to do anything because should not ever EVER be used
	}

	WorldManager& WorldManager::getInstance(){
		static WorldManager single;
		return single;
	}

	WorldManager::WorldManager() {
		m_deletions = std::vector<Object*>();
		m_updates = std::vector<Object*>();
		setType("WorldManager");
		m_boundary = Box(Vector(0, 0), DM.getHorizontal(), DM.getVertical());
		m_view = Box(Vector(0, 0), DM.getHorizontal(), DM.getVertical());
	}

	int WorldManager::startUp()
	{
		if (isStarted()) {
			LM.writeLog("World Manager is already active");
			return -1;
		}
		std::vector<Object*>::iterator it = m_deletions.begin();
		while (it != m_deletions.end()) {
			delete (*it);
			it = m_deletions.begin();
		}
		m_deletions.clear();
		std::vector<Object*>::iterator it2 = m_updates.begin();
		while (it2 != m_updates.end()) {
			delete (*it2);
			it2 = m_updates.begin();
		}
		m_updates.clear();
		return Manager::startUp();
	}

	void WorldManager::shutDown()
	{
		LM.writeLog("Shutting Down World Manager");
		std::vector<Object*>::iterator it = m_deletions.begin();
		while (it != m_deletions.end()) {
			delete (*it);
			it = m_deletions.begin();
		}
		m_deletions.clear();
		std::vector<Object*>::iterator it2 = m_updates.begin();
		while (it2 != m_updates.end()) {
			delete (*it2);
			it2 = m_updates.begin();
		}
		m_updates.clear();
		Manager::shutDown();

	}

	int WorldManager::insertObject(Object* p_o)
	{
		if (!isStarted()) {
			LM.writeLog("ERROR: world manager needs to be started before you can insert an object into it");
			return -1;
		}
		LM.writeLog("Adding Object to World");
		m_updates.insert(m_updates.end(), p_o);
		return 0;
	}

	int WorldManager::removeObject(Object* p_o)
	{
		LM.writeLog("Removing Object from World");
		std::vector<Object*>::iterator it = m_updates.begin();
		while (it != m_updates.end()) {
			if (*it == p_o) {
				m_updates.erase(it);
				LM.writeLog("Removed from updates");
				return 0;
			}
			it++;
		}
		it = m_deletions.begin();
		while (it != m_deletions.end()) {
			if (*it == p_o) {
				m_deletions.erase(it);
				LM.writeLog("Removed from deletions");
				return 0;
			}
			it++;
		}
		LM.writeLog("ERROR: Object does not excist in world");
		return -1;
	}

	std::vector<Object*> WorldManager::getAllObjects() const
	{
		std::vector<Object*> ret = std::vector<Object*>();
		ret.insert(ret.end(), m_updates.begin(), m_updates.end());
		ret.insert(ret.end(), m_deletions.begin(), m_deletions.end());
		return ret;
	}

	void WorldManager::update()
	{
		LM.writeLog("Update Function Ran");
		for (auto x : m_updates) {
			moveObject(x, x->predictPosition());
		}
		std::vector<Object*>::iterator it = m_deletions.begin();
		while (it != m_deletions.end()) {
			delete (*it);
			it = m_deletions.begin();
		}
		m_deletions.clear();
	}

	int WorldManager::markForDelete(Object* p_o)
	{
		LM.writeLog("Object Marked for Deletion");
		int marked = -1;
		std::vector<Object*>::iterator it = m_updates.begin();
		while (it != m_updates.end() && marked == -1) {
			if (*it == p_o) {
				marked = 0;
				m_updates.erase(it);
				break;
			}
			it++;
		}
		if (marked == 0) {
			m_deletions.insert(m_deletions.end(), p_o);
			return 0;
		}
		LM.writeLog("ERROR: object not found for deletion");
		return -1;
	}

	void WorldManager::draw() {
		for (int i = 0; i <= MAX_ALTITUDE; i++) {
			std::vector<Object*>::iterator it = m_updates.begin();
			while (it != m_updates.end()) {
				if (i == (*it)->getAltitude()) {
					Box temp_box = getWorldBox(*it);
					if (boxIntersectsBox(temp_box, m_view) || dynamic_cast <ViewObject *> (*it)) {
						(*it)->draw();
					}
				}
				++it;
			}
		}
	}
	std::vector<Object*> WorldManager::getCollisions(const Object* p_o, Vector where) const
	{
		std::vector<Object*> ret = std::vector<Object*>();
		std::vector<Object*> allObjs = getAllObjects();
		std::vector<Object*>::iterator it = allObjs.begin();
		while (it != allObjs.end()) {
			if ((*it) != p_o) {
				if (boxIntersectsBox(getWorldBoxWithPos(p_o, p_o->predictPosition()), getWorldBox(*it)) && (*it)->isSolid()) {
					ret.push_back((*it));
				}
			}
			it++;
		}


		return ret;
	}
	int WorldManager::moveObject(Object* p_o, Vector where)
	{
		if (p_o->isSolid()) {
			std::vector<Object*> list = getCollisions(p_o, where);
			if (!list.empty()) {
				bool do_move = true;
				std::vector<Object*>::iterator it = list.begin();
				while (it != list.end()) {
					EventCollision ev = EventCollision(p_o, (*it), where);
					p_o->eventHandler(&ev);
					(*it)->eventHandler(&ev);

					if (p_o->getSolidness() == HARD && (*it)->getSolidness() == HARD) {
						do_move = false;
					}
					++it;
				}
				if (!do_move) {
					return -1;
				}
			}

		}
		Box orig_box = getWorldBox(p_o);
		p_o->setPosition(where);
		if (p_view_following == p_o) {
			setViewPosition(p_o->getPosition());
		}
		Box new_box = getWorldBox(p_o);
		if (boxIntersectsBox(orig_box, m_boundary) && !boxIntersectsBox(new_box, m_boundary)) {
			EventOut ov;
			p_o->eventHandler(&ov);
		}
		return 0;
	}
	Box WorldManager::getBoundary() const
	{
		return m_boundary;
	}
	void WorldManager::setBoundary(Box new_boundary)
	{
		m_boundary = new_boundary;
	}
	Box WorldManager::getView() const
	{
		return m_view;
	}
	void WorldManager::setView(Box new_view)
	{
		m_view = new_view;
	}
	void WorldManager::setViewPosition(Vector view_pos)
	{
		float x = view_pos.getX() - m_view.getHorizontal() / 2;
		if (x + m_view.getHorizontal() > m_boundary.getHorizontal()) {
			x = m_boundary.getHorizontal() - m_view.getHorizontal();
		}
		if (x < 0) {
			x = 0;
		}

		float y = view_pos.getY() - m_view.getVertical() / 2;
		if (y + m_view.getVertical() > m_boundary.getVertical()) {
			y = m_boundary.getVertical() - m_view.getVertical();
		}
		if (y < 0) {
			y = 0;
		}
		Vector new_corner(x, y);
		m_view.setCorner(new_corner);
	}
	int WorldManager::setViewFollowing(Object* p_new_view_following)
	{
		if (p_new_view_following == NULL) {
			p_view_following = NULL;
			return 0;
		}
		p_view_following = p_new_view_following;
		setViewPosition(p_view_following->getPosition());
		return 0;
	}
}

