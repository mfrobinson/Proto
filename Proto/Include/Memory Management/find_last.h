#pragma once
#include "Declarations/Memory Management/find_last.h"


namespace Proto {

	template <typename TYPE>
	size_t find_last(const TYPE* source, const TYPE& value, const size_t searchable_length) {
		for (size_t i = searchable_length; i > 0; --i) {
			if (source[i - 1] == value) {
				return i - 1;
			}
		}
		throw std::runtime_error("Unable to find the specified value!");
	}

}