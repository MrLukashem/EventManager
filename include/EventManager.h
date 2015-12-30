
/*
Copyright [2015] [Łukasz Merta]

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

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

	constexpr static int STOCK_FREE_LISTENER_ID = 0;

	int m_freeTypeID = STOCK_FREE_TYPE_ID;

	int m_freeListenerID = STOCK_FREE_LISTENER_ID;

	std::vector<ListenerBase*> m_listenersVec;

	static std::unique_ptr<EventManager> m_me;

	EventManager() {
		m_me = std::unique_ptr<EventManager>{this};
	}
public:
	static std::unique_ptr<EventManager>& getInstance() {
		return m_me;
	}

	virtual ~EventManager() {}

	template <typename CustomEvent>
	void send(CustomEvent&);

	template <typename CustomEvent>
	int listen(EventListener<CustomEvent>&);

	template <typename CustomEvent>
	void unlisten(EventListener<CustomEvent>&);

	void unlistenByID(int);

	template <typename CustomEvent>
	void registerEvent();	
};

template <typename CustomEvent>
void EventManager::send(CustomEvent& event) {
	static_assert(std::is_base_of<Event, CustomEvent>::value, TEMPLATE_PARAM_ERROR);

	auto event_receivers_vec 
		= std::find_if(m_listenersVec.begin(), m_listenersVec.end(), [] (auto base) {
			return base->getType() == CustomEvent::m_type;
		});

	for(auto listener : event_receivers_vec) {
		listener->invoke(event);
	}
}

template <typename CustomEvent>
int EventManager::listen(EventListener<CustomEvent>& listener) {
	static_assert(std::is_base_of<Event, CustomEvent>::value, TEMPLATE_PARAM_ERROR);

	m_listenersVec.push_back(&listener);
	listener.setID(m_freeListenerID++);

	return listener.getID();
}

template <typename CustomEvent>
void EventManager::unlisten(EventListener<CustomEvent>& listener) {
	std::remove_if(m_listenersVec.begin(), m_listenersVec.end(), 
		[&] (auto base) {
			return base->getID() == listener.getID();
		});
}

template <typename CustomEvent>
void EventManager::registerEvent() {
	static_assert(std::is_base_of<Event, CustomEvent>::value, TEMPLATE_PARAM_ERROR);

	CustomEvent::m_type = m_freeTypeID;
	++m_freeTypeID;
}

} //eternity

#endif