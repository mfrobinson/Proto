#pragma once
#include "Data Structures/Dictionary/AbstractDictionary.h"


namespace Proto {

	template <typename KEY_TYPE, typename VALUE_TYPE>
	bool has_key(const AbstractDictionary<KEY_TYPE, VALUE_TYPE>& dictionary, const KEY_TYPE& key);

}