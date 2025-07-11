#pragma once
#include "Declarations/Data Structures/Dictionary/has_key.h"


namespace Proto {

	template <typename KEY_TYPE, typename VALUE_TYPE>
	bool has_key(const AbstractDictionary<KEY_TYPE, VALUE_TYPE>& dictionary, const KEY_TYPE& key) {
		for (size_t i = 0; i < dictionary.length(); ++i) {
			if (dictionary.key_at(i) == key) {
				return true;
			}
		}
		return false;
	}

}