
#include "Event.h"

namespace eternity {
	int Event::m_type = 0;

	int Event::getValue() const {
		return m_value;
	}

	void Event::setValue(int new_value) {
		m_value = new_value;
	}
}