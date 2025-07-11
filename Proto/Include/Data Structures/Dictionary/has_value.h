#pragma once
#include "Declarations/Data Structures/Dictionary/has_value.h"


namespace Proto {

	template <typename KEY_TYPE, typename VALUE_TYPE>
	bool has_value(const AbstractDictionary<KEY_TYPE, VALUE_TYPE>& dictionary, const VALUE_TYPE& value) {
		for (size_t i = 0; i < dictionary.length(); ++i) {
			if (dictionary.value_at(i) == value) {
				return true;
			}
		}
		return false;
	}

}