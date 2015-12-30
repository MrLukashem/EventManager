
#include "EventManager.h"

namespace eternity {

void EventManager::unlistenByID(int listener_id) {
	std::remove_if(m_listenersVec.begin(), m_listenersVec.end(), 
		[=] (auto base) {
			return base->getID() == listener_id;
		});
}

} //eternity