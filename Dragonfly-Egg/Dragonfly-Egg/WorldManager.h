#pragma once
#ifndef __WORLDMANAGER_H__
#define __WORLDMANAGER_H__
#include "Manager.h"
#include <vector>
#include "Object.h"

#define WM df::WorldManager::getInstance()
namespace df {
	class WorldManager : public Manager {
	private:
		WorldManager(); //no creation because singleton
		WorldManager(WorldManager const&); //no assignment
		void operator=(WorldManager const&); //no copying
		std::vector<Object *> m_updates; //list of all objects in world
		std::vector<Object*> m_deletions; //list of all objects cued for deletion
		Box m_boundary; // world boundary
		Box m_view; //player view of game world
		Object* p_view_following; //Object view is following.

	public:
		static WorldManager& getInstance(); //get the one and only instance of WorldManager

		int startUp(); //Startup the gameworld (Initialize everything to empty) returns 0

		void shutDown(); //shutdown game world (delete all game world objects)

		int insertObject(Object* p_o); // add object to world. Return 0 if ok, else -1

		int removeObject(Object* p_o); // remove object from world. Retruns 0 if ok else -1

		std::vector<Object*> getAllObjects() const; //return list of all objects in world 

		void update(); //update world Delete objects marked for deletion

		int markForDelete(Object* p_o); //indicate object is to be deleted at end of current game update. Return 0 if ok, else -1

		void draw(); //draw all objects

		std::vector<Object*> getCollisions(const Object* p_o, Vector where) const; //get all objects that are colliding with given object

		int moveObject(Object* p_o, Vector where); // move an object to a location

		Box getBoundary() const; // get the boundary

		void setBoundary(Box new_boundary); // set the boundary

		Box getView() const; // get player view of game world

		void setView(Box new_view); // set player view of game world

		void setViewPosition(Vector view_pos); //set view to center creen on position view_pos. view edge will not go beyond world boundary

		int setViewFollowing(Object* p_new_view_following); // set view to center screen on object. set to null to stop following. if p_new_view_following not legit, return -1 else return 0.
	};
}




#endif // !__WORLDMANAGER_H__



