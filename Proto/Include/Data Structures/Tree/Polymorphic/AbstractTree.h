#pragma once
#include "Declarations/Data Structures/Tree/Polymorphic/AbstractTree.h"
#include "Data Structures/Dictionary/ArrayDictionary.h"


namespace Proto {

	namespace Polymorphic {

		template <typename INDEX_TYPE, typename STORED_TYPE>
		AbstractTree<INDEX_TYPE, STORED_TYPE>::~AbstractTree() {
			return;
		}

		template <typename INDEX_TYPE, typename STORED_TYPE>
		size_t AbstractTree<INDEX_TYPE, STORED_TYPE>::height() const noexcept {
			ArrayDictionary<INDEX_TYPE, const AbstractTree<INDEX_TYPE, STORED_TYPE>*> children;
			this->children(&children);
			size_t height = 0;
			size_t next_height;
			for (size_t i = 0; i < children.length(); ++i) {
				next_height = children.value_at(i)->height();
				if (next_height > height) {
					height = next_height;
				}
			}
			return height + 1;
		}

		template <typename INDEX_TYPE, typename STORED_TYPE>
		std::ostream& AbstractTree<INDEX_TYPE, STORED_TYPE>::visualise(std::ostream& os, const String& prefix) const {
			ArrayDictionary<INDEX_TYPE, const AbstractTree<INDEX_TYPE, STORED_TYPE>*> children;
			this->children(&children);
			size_t number_of_children = children.length();
			os << this->value() << "\n";
			const AbstractTree<INDEX_TYPE, STORED_TYPE>* child;
			for (size_t i = 0; i < number_of_children; ++i) {
				os << prefix << "|-";
				child = children.value_at(i);
				if (i + 1 < number_of_children) {
					child->visualise(os, prefix + "| ");
				}
				else {
					child->visualise(os, prefix + "  ");
				}
			}
			return os;
		}

		template <typename INDEX_TYPE, typename STORED_TYPE>
		std::ostream& operator<<(std::ostream& os, const AbstractTree<INDEX_TYPE, STORED_TYPE>& tree) {
			return tree.visualise(os);
		}

	}
}