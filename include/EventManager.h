
#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <type_traits>
#include <memory>
#include <vector>
#include <algorithm>

#include "Event.h"
#include "EventListener.h"

namespace eternity {

class EventManager {
	constexpr static int STOCK_FREE_TYPE_ID = 10;

	int m_freeTypeID = STOCK_FREE_TYPE_ID;

	std::vector<ListenerBase*> m_listenersVec;

	EventManager() {}
public:
	std::unique_ptr<EventManager>& getInstance();

	virtual ~EventManager() {}

	//std::is_same ?
	template <typename CustomEvent>
	void send(CustomEvent&);

	template <typename CustomEvent>
	void listen(EventListener<CustomEvent>&);

	template <typename E>
	void registerEvent() {
		static_assert(std::is_base_of<Event, E>::value, TEMPLATE_PARAM_ERROR);

		E::m_type = m_freeTypeID;
		++m_freeTypeID;
	}	
};

template <typename CustomEvent>
void EventManager::send(CustomEvent& event) {
	static_assert(std::is_base_of<Event, CustomEvent>::value, TEMPLATE_PARAM_ERROR);

	auto event_receivers_vec 
		= std::find_if(m_listenersVec.begin(), m_listenersVec.end(), [](ListenerBase* base) -> bool {
			return base->getType() == CustomEvent::m_type;
		});

	for(auto listener : event_receivers_vec) {
		listener->invoke(event);
	}
}

template <typename CustomEvent>
void EventManager::listen(EventListener<CustomEvent>& listener) {
	static_assert(std::is_base_of<Event, CustomEvent>::value, TEMPLATE_PARAM_ERROR);
	
	m_listenersVec.push_back(&listener);
}

} //eternity

#endif