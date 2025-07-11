#pragma once


namespace Proto {

	template <typename TYPE>
	size_t count(const TYPE* from, const TYPE& value, const size_t length) {
		size_t counted = 0;
		for (size_t i = 0; i < length; ++i) {
			if (from[i] == value) {
				++counted;
			}
		}
		return counted;
	}

}