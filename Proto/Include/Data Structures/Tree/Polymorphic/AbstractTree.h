#pragma once
#include "Declarations/Data Structures/Tree/Polymorphic/AbstractTree.h"


namespace Proto {

	namespace Polymorphic {

		template <typename TYPE>
		AbstractTree<TYPE>::~AbstractTree() {
			return;
		}

		template <typename TYPE>
		size_t AbstractTree<TYPE>::height() const noexcept {
			size_t number_of_children = this->number_of_children();
			const AbstractTree<TYPE>* child;
			size_t greatest_sub_height = 0;
			for (size_t i = 0; i < number_of_children; ++i) {
				child = this->child(i);
				if (child != nullptr) {
					if (child->height() > greatest_sub_height) {
						greatest_sub_height = child->height();
					}
				}
			}
			return greatest_sub_height + 1;
		}

		template <typename TYPE>
		std::ostream& AbstractTree<TYPE>::visualise(std::ostream& os, const String& prefix) const {
			os << this->value() << "\n";
			size_t number_of_children = this->number_of_children();
			const AbstractTree<TYPE>* child;
			for (size_t i = 0; i < number_of_children; ++i) {
				os << prefix << "|-";
				child = this->child(i);
				if (child != nullptr) {
					if (i + 1 < number_of_children) {
						child->visualise(os, prefix + "| ");
					}
					else {
						child->visualise(os, prefix + "  ");
					}
				}
				else {
					os << "\n";
				}
			}
			return os;
		}

		template <typename TYPE>
		std::ostream& operator<<(std::ostream& os, const AbstractTree<TYPE>& tree) {
			return tree.visualise(os);
		}

	}

}