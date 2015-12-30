
#include <iostream>
#include "EventListener.h"
#include "EventManager.h"

class CE : public eternity::Event {

public:
	void show() {
		std::cout << "to ja, custom!!!";
	}
};

using namespace eternity;

int main() {
	auto p = 4;

	auto fn = [](CE e) {};
	eternity::EventListener<CE> eventListener([](CE e) {
			e.show();
		//std::cout << "Tu doszedlem!";
	});

	//eventListener(eternity::Event{});

	std::cout << eventListener.getType();

	Event e{};
	eventListener.invoke(e);

	//static_cast<CE>(e);
	//eternity::EventManager manager{};
	//	manager.registerEvent<eternity::Event>();
}