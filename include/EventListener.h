
#include <type_traits>
#include <functional>

#include "Event.h"

#ifndef EVENT_LISTENER_H
#define EVENT_LISTENER_H

#include <iostream>

#define TEMPLATE_PARAM_ERROR "Template argument should extends Event!"

namespace eternity {

class ListenerBase {
public:
	virtual void invoke(Event&) = 0;

	virtual int getType() const = 0 ;
};

template <typename E>
class EventListener : public ListenerBase {
public:
	using EventReceiverFn = std::function<void(E&)>;
private:
	static_assert(std::is_base_of<Event, E>::value, TEMPLATE_PARAM_ERROR);

	int m_type;

	EventReceiverFn m_callback;
public:
	void invoke(Event& event) {
		E* casted_class = dynamic_cast<E*>(&event);
		if(casted_class != nullptr) {
			m_callback(*casted_class);
		}
	}
public:
	EventListener(EventReceiverFn callback) 
	: m_type{E::m_type}, m_callback{callback} {}

	virtual ~EventListener() {}

	virtual int inline getType() const final {
		return m_type;
	}

	virtual void inline operator()(E& event) {
		m_callback(event);
	}

	virtual void inline operator()(E&& event) {
		m_callback(event);
	}
}; //EventListener

} //eternity

#endif