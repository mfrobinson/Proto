#pragma once
#include "Declarations/Data Structures/Dictionary/AbstractDictionary.h"


namespace Proto {

	template <typename KEY_TYPE, typename VALUE_TYPE>
	AbstractDictionary<KEY_TYPE, VALUE_TYPE>::~AbstractDictionary() noexcept {
		return;
	}

	template <typename KEY_TYPE, typename VALUE_TYPE>
	std::ostream& operator<<(std::ostream& os, const AbstractDictionary<KEY_TYPE, VALUE_TYPE>& dictionary) {
		os << "{";
		for (size_t i = 0; i < dictionary.length(); ++i) {
			os << dictionary.key_at(i) << ":" << dictionary.value_at(i);
			if (i + 1 < dictionary.length()) {
				os << ",";
			}
		}
		os << "}";
		return os;
	}

	template <typename KEY_TYPE, typename VALUE_TYPE>
	bool operator==(const AbstractDictionary<KEY_TYPE, VALUE_TYPE>& lhs, const AbstractDictionary<KEY_TYPE, VALUE_TYPE>& rhs) {
		if (lhs.length() != rhs.length()) {
			return false;
		}
		for (size_t i = 0; i < lhs.length(); ++i) {
			if (lhs.key_at(i) != rhs.key_at(i) || lhs.value_at(i) != rhs.value_at(i)) {
				return false;
			}
		}
		return true;
	}

}