#pragma once
#include "Memory Management/Pointers/Optional.h"


namespace Proto {

	struct HuffmanNode {
		size_t occurrences;
		Optional<char> character;
	};

}