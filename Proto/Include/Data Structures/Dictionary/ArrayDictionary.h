#pragma once
#include "Data Structures/Dictionary/ListStoredDictionary.h"
#include "Data Structures/List/ArrayList.h"


namespace Proto {

	template <typename K, typename V>
	using ArrayDictionary = ListStoredDictionary<ArrayList, K, V>;

}