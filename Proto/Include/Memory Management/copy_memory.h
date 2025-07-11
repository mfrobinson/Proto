#pragma once


namespace Proto {

	template <typename TYPE>
	void copy_memory(const TYPE* from, TYPE* to, const size_t count) {
		for (size_t i = 0; i < count; ++i) {
			to[i] = from[i];
		}
		return;
	}

}