#pragma once


namespace Proto {

	template <typename TYPE>
	bool compare_memory(const TYPE* lhs, const TYPE* rhs, const size_t count) {
		for (size_t i = 0; i < count; ++i) {
			if (lhs[i] != rhs[i]) {
				return false;
			}
		}
		return true;
	}

}