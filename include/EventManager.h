
#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

class EventManager {
	
public:
	bool send(Event*);

	bool listen(EventListener&);
};

#endif