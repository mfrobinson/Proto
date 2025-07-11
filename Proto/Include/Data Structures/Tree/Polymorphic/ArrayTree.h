#pragma once
#include "Data Structures/Tree/Polymorphic/ListStoredTree.h"
#include "Data Structures/List/ArrayList.h"


namespace Proto {

	namespace Polymorphic {

		template <typename TYPE>
		using ArrayTree = ListStoredTree<ArrayList, TYPE>;

	}

}