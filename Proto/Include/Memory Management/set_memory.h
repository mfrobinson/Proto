#pragma once
#include "Declarations/Memory Management/set_memory.h"


namespace Proto {

	template <typename T>
	void set_memory(T* target, const T& value, const size_t instances) {
		for (size_t i = 0; i < instances; ++i) {
			target[i] = value;
		}
		return;
	}

}