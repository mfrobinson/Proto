#pragma once
#include "Declarations/Data Structures/List/AbstractList.h"


namespace Proto {

	template <typename TYPE>
	AbstractList<TYPE>::~AbstractList() noexcept {
		return;
	}

	template <typename TYPE>
	std::ostream& operator<<(std::ostream& os, const AbstractList<TYPE>& list) {
		os << "[";
		for (size_t i = 0; i < list.length(); ++i) {
			os << list.get(i);
			if (i + 1 < list.length()) {
				os << ",";
			}
		}
		os << "]";
		return os;
	}

}