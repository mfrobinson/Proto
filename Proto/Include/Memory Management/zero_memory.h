#pragma once
#include "Declarations/Memory Management/zero_memory.h"
#include "Memory Management/set_memory.h"


namespace Proto {

	template <typename T>
	void zero_memory(T* target, const size_t instances) {
		set_memory<char>((char*)target, 0, sizeof(T) * instances);
		return;
	}

}