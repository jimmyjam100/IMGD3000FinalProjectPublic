#include "Manager.h"
#include "LogManager.h"

namespace df {
	void Manager::setType(std::string type){
		m_type = type;
	}

	Manager::Manager(){
		m_is_started = false;
		m_type = "Manager";
	}

	Manager::~Manager(){

	}

	std::string Manager::getType() const {
		return std::string();
	}

	int Manager::startUp()
	{
		m_is_started = true;
		return 0;
	}

	void Manager::shutDown()
	{
		m_is_started = false;
	}

	bool Manager::isStarted() const
	{
		return m_is_started;
	}
}

