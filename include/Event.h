
#ifndef EVENT_H
#define EVENT_H

namespace eternity {

class Event {
	friend class EventManager;

	template <typename CustomEvent>
	friend class EventListener;

	static int m_type;

	int m_value;
public:
	Event() : m_value{} {}

	virtual int getType() const final {
		return m_type;
	}

	virtual int getValue() const;

	virtual void setValue(int);
};

}; //eternity

#endif