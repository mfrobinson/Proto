#pragma once
#include "Declarations/Data Structures/Tree/Polymorphic/BinaryTree.h"


namespace Proto {

	namespace Polymorphic {

		template <typename TYPE>
		Pointer<AbstractTree<TYPE>> BinaryTree<TYPE>::clone() const {
			return PolymorphicPointer<AbstractTree<TYPE>>(*this);
		}

		template <typename TYPE>
		std::ostream& BinaryTree<TYPE>::visualise(std::ostream& os, const String& prefix) const {
			os << this->value() << "\n";
			const char* branch_texts[] = { "|-L-", "|-R-" };
			const char* prefix_texts[] = { "|   ", "    " };
			for (size_t i = 0; i < 2; ++i) {
				if (this->child(i) != nullptr) {
					os << prefix << branch_texts[i];
					this->child(i)->visualise(os, prefix + prefix_texts[i]);
				}
			}
			return os;
		}

	}

}