#pragma once
#include "Declarations/Data Structures/Tree/Polymorphic/NTree.h"
#include "Memory Management/Pointers/Optional.h"
#include "Memory Management/Pointers/PolymorphicPointer.h"
#include "Cast/move_cast.h"
#include "Memory Management/copy.h"


namespace Proto {

	namespace Polymorphic {

		template <size_t N, typename TYPE>
		NTree<N,TYPE>::NTree() : AbstractValuedTree<TYPE>() {
			return;
		}

		template <size_t N, typename TYPE>
		NTree<N, TYPE>::NTree(NTree<N, TYPE>&& other) : AbstractValuedTree<TYPE>(move_cast(other)) {
			this->_move_(other);
			return;
		}

		template <size_t N, typename TYPE>
		NTree<N, TYPE>::NTree(const NTree<N, TYPE>& other) : AbstractValuedTree<TYPE>(other) {
			this->_copy_(other);
			return;
		}

		template <size_t N, typename TYPE>
		NTree<N, TYPE>& NTree<N, TYPE>::operator=(NTree<N, TYPE>&& other) {
			if (&other != this) {
				this->_cleanup_();
				this->_super_cleanup_();
				this->_super_move_(other);
				this->_move_(other);
			}
			return *this;
		}

		template <size_t N, typename TYPE>
		NTree<N, TYPE>& NTree<N, TYPE>::operator=(const NTree<N, TYPE>& other) {
			if (&other != this) {
				this->_cleanup_();
				this->_super_cleanup_();
				this->_super_copy_(other);
				this->_copy_(other);
			}
			return *this;
		}

		template <size_t N, typename TYPE>
		NTree<N, TYPE>::~NTree() {
			this->_cleanup_();
			return;
		}

		template <size_t N, typename TYPE>
		NTree<N, TYPE>::NTree(TYPE root_value) : AbstractValuedTree<TYPE>(move_cast(root_value)) {
			return;
		}

		// Add the child to the least height subtree
		template <size_t N, typename TYPE>
		void NTree<N, TYPE>::add(Pointer<AbstractTree<TYPE>>& child) {
			AbstractTree<TYPE>* current = nullptr;
			AbstractTree<TYPE>* least_height_subtree = nullptr;
			Pointer<size_t> least_height;
			for (size_t i = 0; i < this->number_of_children(); ++i) {
				if (this->child_trees[i] == nullptr) {
					this->insert(i, child);
					return;
				}
				if (least_height == nullptr) {
					least_height = Pointer<size_t>(this->child_trees[i]->height());
					least_height_subtree = this->child_trees[i];
				}
				else {
					if (this->child_trees[i]->height() < *least_height) {
						*least_height = this->child_trees[i]->height();
						least_height_subtree = this->child_trees[i];
					}
				}
			}
			least_height_subtree->add(child);
			return;
		}

		template <size_t N, typename TYPE>
		void NTree<N, TYPE>::insert(const size_t position, Pointer<AbstractTree<TYPE>>& subtree) {
			if (position >= N) {
				throw std::runtime_error("Cannot add tree as the index is out of bounds!");
			}
			if (this->child_trees[position] != nullptr) {
				this->child_trees[position]->add(subtree);
				return;
			}
			this->child_trees[position] = move_cast(subtree);
			return;
		}

		template <size_t N, typename TYPE>
		void NTree<N, TYPE>::remove(const size_t index) {
			if (index >= N) {
				throw std::runtime_error("Cannot remove tree as the index is out of bounds!");
			}
			this->child_trees[index] = (Pointer<AbstractTree<TYPE>>&&)Pointer<AbstractTree<TYPE>>();
			return;
		}

		template <size_t N, typename TYPE>
		size_t NTree<N, TYPE>::number_of_children() const noexcept {
			return N;
		}

		template <size_t N, typename TYPE>
		AbstractTree<TYPE>* NTree<N, TYPE>::child(const size_t index) {
			if (index >= N) {
				throw std::runtime_error("Cannot remove tree as the index is out of bounds!");
			}
			return this->child_trees[index];
		}

		template <size_t N, typename TYPE>
		const AbstractTree<TYPE>* NTree<N, TYPE>::child(const size_t index) const {
			if (index >= N) {
				throw std::runtime_error("Cannot remove tree as the index is out of bounds!");
			}
			return this->child_trees[index];
		}

		template <size_t N, typename TYPE>
		Pointer<AbstractTree<TYPE>> NTree<N, TYPE>::clone() const {
			return PolymorphicPointer<AbstractTree<TYPE>>(*this);
		}

		template <size_t N, typename TYPE>
		inline void NTree<N, TYPE>::_move_(NTree<N, TYPE>& other) {
			for (size_t i = 0; i < N; ++i) {
				this->child_trees[i] = move_cast(other.child_trees[i]);
			}
			return;
		}

		template <size_t N, typename TYPE>
		inline void NTree<N, TYPE>::_copy_(const NTree<N, TYPE>& other) {
			const AbstractTree<TYPE>* other_child;
			for (size_t i = 0; i < N; ++i) {
				other_child = other.child_trees[i];
				if (other_child != nullptr) {
					this->child_trees[i] = other_child->clone();
				}
			}
			return;
		}

		template <size_t N, typename TYPE>
		inline void NTree<N, TYPE>::_cleanup_() {
			return;
		}

		template <size_t N, typename TYPE>
		inline void NTree<N, TYPE>::_super_move_(NTree<N, TYPE>& other) {
			AbstractValuedTree<TYPE>::_move_(other);
			return;
		}

		template <size_t N, typename TYPE>
		inline void NTree<N, TYPE>::_super_copy_(const NTree<N, TYPE>& other) {
			AbstractValuedTree<TYPE>::_copy_(other);
			return;
		}

		template <size_t N, typename TYPE>
		inline void NTree<N, TYPE>::_super_cleanup_() {
			AbstractValuedTree<TYPE>::_cleanup_();
			return;
		}

	}

}