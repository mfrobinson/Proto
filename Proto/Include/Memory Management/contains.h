#pragma once
#include "compare_memory.h"
#include <iostream>
#include "Memory Management/Pointers/Array.h"


namespace Proto {

	template <typename TYPE>
	bool contains(const TYPE* source, const TYPE& target, const size_t source_length) {
		for (size_t i = 0; i < source_length; ++i) {
			if (source[i] == target) {
				return true;
			}
		}
		return false;
	}

	template <typename TYPE>
	bool contains(const TYPE* source, const TYPE* target, const size_t target_length, const size_t source_length) {
		if (target_length >= source_length) {
			return false;
		}
		for (size_t i = 0; i < (source_length + 1) - target_length; ++i) {
			if (Proto::compare_memory<char>(source + i, target, target_length)) {
				return true;
			}
		}
		return false;
	}

}