
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

#include "Event.h"

#ifndef EVENT_LISTENER_H
#define EVENT_LISTENER_H


#include <type_traits>
#include <functional>
#include <iostream>

#define TEMPLATE_PARAM_ERROR "Template argument should extends Event!"

namespace eternity {

class ListenerBase {
	friend class EventManager;

	int m_id;

	virtual void setID(int id) {
		m_id = id;
	}
public:
	virtual void invoke(Event&) = 0;

	virtual int getType() const = 0 ;

	virtual int getID() const final {
		return m_id;
	}
}; //ListenerBase

template <typename E>
class EventListener : public ListenerBase {
public:
	using EventReceiverFn = std::function<void(E&)>;
private:
	static_assert(std::is_base_of<Event, E>::value, TEMPLATE_PARAM_ERROR);

	int m_type;

	EventReceiverFn m_callback;
public:
	void invoke(Event& event) override {
		E* casted_class = dynamic_cast<E*>(&event);
		
		if(casted_class != nullptr) {
			m_callback(*casted_class);
		}
	}
public:
	EventListener(EventReceiverFn callback) 
	: m_type{E::m_type}, m_callback{callback} {}

	virtual ~EventListener() {}

	virtual int inline getType() const final override {
		return m_type;
	}

	virtual void inline operator()(E& event) {
		m_callback(event);
	}

	virtual void inline operator()(E&& event) {
		m_callback(event);
	}

	virtual void inline operator()(Event& event) {
		invoke(event);
	}

	virtual void inline operator()(Event&& event) {
		invoke(event);
	}
}; //EventListener

} //eternity

#endif