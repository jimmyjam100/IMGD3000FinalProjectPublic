#pragma once
#ifndef __MANAGER_H__
#define __MANAGER_H__


#include <string>
#include <iostream>

namespace df {
		class Manager {
		private:
			std::string m_type; // manager type
			bool m_is_started; // true if the manager has started. false otherwise
		protected:
			void setType(std::string type); // set the type of manager
		public:
			Manager(); // default constructer
			virtual ~Manager(); // deletes the manager
			std::string getType() const; // gets the type of the manager
			virtual int startUp(); // starts up the manager
			virtual void shutDown(); // shuts down the manager
			bool isStarted() const; // returns weather the manager was started or not
	};
} // end of namespace df

#endif //__MANAGER_H__