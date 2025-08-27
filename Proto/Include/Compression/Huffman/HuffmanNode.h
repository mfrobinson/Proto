#pragma once
#include "Declarations/Compression/Huffman/HuffmanNode.h""


namespace Proto {

	template <typename KEY_TYPE, typename VALUE_TYPE>
	std::ostream& operator<<(std::ostream& os, const HuffmanNode& node) {
		if (node.character.has_value()) {
			os << *node.character << " ";
		}
		os << "(" << node.frequency << ")";
		return os;
	}

}