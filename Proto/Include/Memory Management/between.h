#pragma once
#include "Declarations/Memory Management/between.h"


namespace Proto {

	template <typename TYPE>
	bool between(const TYPE& value, const TYPE& lower_bound, const TYPE& upper_bound) {
		return value >= lower_bound && value <= upper_bound;
	}

}