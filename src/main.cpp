
#include <iostream>
#include "EventListener.h"

int main() {
	auto p = 4;

	auto fn = [](eternity::Event e) {};
	eternity::EventListener<eternity::Event> eventListener([](eternity::Event e) {
		std::cout << "hello event\n";
	});

	eventListener(eternity::Event{});

	std::cout << eventListener.getType();

	std::cout << "Hello!";
}