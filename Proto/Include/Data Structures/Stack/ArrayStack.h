#pragma once
#include "Data Structures/Stack/ListStoredStack.h"
#include "Data Structures/List/ArrayList.h"


namespace Proto {

	template <typename TYPE>
	using ArrayStack = ListStoredStack<ArrayList, TYPE>;

}