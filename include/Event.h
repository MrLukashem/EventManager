
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