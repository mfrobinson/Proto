#pragma once
#include "Declarations/Memory Management/move_memory.h"


namespace Proto {

	template <typename TYPE>
	void move_memory(TYPE* from, TYPE* to, const size_t count) {
		for (size_t i = 0; i < count; ++i) {
			to[i] = move_cast(from[i]);
		}
		return;
	}

}