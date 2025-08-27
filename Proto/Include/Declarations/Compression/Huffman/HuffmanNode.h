#pragma once
#include "Memory Management/Pointers/Optional.h"
#include <iostream>


namespace Proto {

	struct HuffmanNode {
		size_t frequency;
		Optional<char> character;
	};

	template <typename KEY_TYPE, typename VALUE_TYPE>
	std::ostream& operator<<(std::ostream& os, const HuffmanNode& node);

}