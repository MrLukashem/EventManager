
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