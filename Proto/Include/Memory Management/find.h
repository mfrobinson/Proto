#pragma once
#include "Memory Management/compare_memory.h"


namespace Proto {

	template <typename TYPE>
	size_t find(const TYPE* source, const TYPE& value) {
		size_t i = 0;
		while (true) {
			if (source[i] == value) {
				return i;
			}
			++i;
		}
	}

	template <typename TYPE>
	size_t find(const TYPE* source, const TYPE* target, const size_t target_length) {
		size_t i = 0;
		while (true) {
			if (Proto::compare_memory<TYPE>(source + i, target, target_length)) {
				return i;
			}
			++i;
		}
	}

}