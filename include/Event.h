
#ifndef EVENT_H
#define EVENT_H

namespace eternity {

class Event {
	friend class EventManager;
public:
	static int m_type;

	virtual int getType() const final {
		return 0;
	}
};

}; //eternity

#endif