
#include <type_traits>
#include <functional>

#include "Event.h"

#ifndef EVENT_LISTENER_H
#define EVENT_LISTENER_H

#define TEMPLATE_PARAM_ERROR "Template argument should extends Event!"

namespace eternity {

template <typename E>
class EventListener {
public:
	using EventReceiverFn = std::function<void(E&)>;
private:
	static_assert(std::is_base_of<E, Event>::value, TEMPLATE_PARAM_ERROR);

	int m_type;

	EventReceiverFn m_callback;
public:
	EventListener(EventReceiverFn callback) 
	: m_type{E::getType()}, m_callback{callback} {}

	virtual ~EventListener() {}

	int inline getType() const {
		return m_type;
	}

	void inline operator()(E& event) {
		m_callback(event);
	}

	void inline operator()(E&& event) {
		m_callback(event);
	}
}; //EventListener

} //eternity

#endif