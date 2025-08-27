#pragma once
#include "Declarations/Data Structures/Tree/Polymorphic/ListStoredTree.h"
#include "Memory Management/Pointers/PolymorphicPointer.h"


namespace Proto {

	namespace PolymorphicOLD {

		template <template <typename> typename LIST_TYPE, typename TYPE>
		ListStoredTree<LIST_TYPE, TYPE>::ListStoredTree() : AbstractValuedTree<TYPE>() {
			return;
		}

		template <template <typename> typename LIST_TYPE, typename TYPE>
		ListStoredTree<LIST_TYPE, TYPE>::ListStoredTree(ListStoredTree<LIST_TYPE, TYPE>&& other) : AbstractValuedTree<TYPE>(move_cast(other)), subtrees(move_cast(other.subtrees)) {
			return;
		}

		template <template <typename> typename LIST_TYPE, typename TYPE>
		ListStoredTree<LIST_TYPE, TYPE>::ListStoredTree(const ListStoredTree<LIST_TYPE, TYPE>& other) : AbstractValuedTree<TYPE>(other) {
			this->_copy_(other);
			return;
		}

		template <template <typename> typename LIST_TYPE, typename TYPE>
		ListStoredTree<LIST_TYPE, TYPE>& ListStoredTree<LIST_TYPE, TYPE>::operator=(ListStoredTree<LIST_TYPE, TYPE>&& other) {
			if (&other != this) {
				this->_cleanup_();
				this->_super_cleanup_();
				this->_super_move_(other);
				this->_move_(other);
			}
			return *this;
		}

		template <template <typename> typename LIST_TYPE, typename TYPE>
		ListStoredTree<LIST_TYPE, TYPE>& ListStoredTree<LIST_TYPE, TYPE>::operator=(const ListStoredTree<LIST_TYPE, TYPE>& other) {
			if (&other != this) {
				this->_cleanup_();
				this->_super_cleanup_();
				this->_super_copy_(other);
				this->_copy_(other);
			}
			return *this;
		}

		template <template <typename> typename LIST_TYPE, typename TYPE>
		ListStoredTree<LIST_TYPE, TYPE>::~ListStoredTree() {
			this->_cleanup_();
			return;
		}

		template <template <typename> typename LIST_TYPE, typename TYPE>
		ListStoredTree<LIST_TYPE, TYPE>::ListStoredTree(TYPE root_value) : AbstractValuedTree<TYPE>(move_cast(root_value)) {
			return;
		}

		template <template <typename> typename LIST_TYPE, typename TYPE>
		void ListStoredTree<LIST_TYPE, TYPE>::add(Pointer<AbstractTree<TYPE>>& subtree) {
			this->subtrees.append(move_cast(subtree));
			return;
		}

		template <template <typename> typename LIST_TYPE, typename TYPE>
		void ListStoredTree<LIST_TYPE, TYPE>::insert(const size_t position, Pointer<AbstractTree<TYPE>>& subtree) {
			if (position > this->subtrees.length()) {
				throw std::runtime_error("Cannot insert into tree - Index out of bounds!");
			}
			if (position == this->subtrees.length()) {
				this->subtrees.append(move_cast(subtree));
				return;
			}
			if (this->subtrees.get(position) == nullptr) {
				this->subtrees.get(position) = move_cast(subtree);
			}
			else {
				this->subtrees.get(position)->add(subtree);
			}
			return;
		}

		template <template <typename> typename LIST_TYPE, typename TYPE>
		void ListStoredTree<LIST_TYPE, TYPE>::remove(const size_t position) {
			this->subtrees.pop(position);
			return;
		}

		template <template <typename> typename LIST_TYPE, typename TYPE>
		size_t ListStoredTree<LIST_TYPE, TYPE>::number_of_children() const noexcept {
			return this->subtrees.length();
		}

		template <template <typename> typename LIST_TYPE, typename TYPE>
		AbstractTree<TYPE>* ListStoredTree<LIST_TYPE, TYPE>::child(const size_t position) {
			return this->subtrees.get(position);
		}

		template <template <typename> typename LIST_TYPE, typename TYPE>
		const AbstractTree<TYPE>* ListStoredTree<LIST_TYPE, TYPE>::child(const size_t position) const {
			return this->subtrees.get(position);
		}

		template <template <typename> typename LIST_TYPE, typename TYPE>
		Pointer<AbstractTree<TYPE>> ListStoredTree<LIST_TYPE, TYPE>::clone() const {
			return PolymorphicPointer<AbstractTree<TYPE>>(*this);
		}

		template <template <typename> typename LIST_TYPE, typename TYPE>
		inline void ListStoredTree<LIST_TYPE, TYPE>::_move_(ListStoredTree<LIST_TYPE, TYPE>& other) {
			this->subtrees = move_cast(other.subtrees);
			return;
		}

		template <template <typename> typename LIST_TYPE, typename TYPE>
		inline void ListStoredTree<LIST_TYPE, TYPE>::_copy_(const ListStoredTree<LIST_TYPE, TYPE>& other) {
			this->subtrees = LIST_TYPE<Pointer<AbstractTree<TYPE>>>();
			for (size_t i = 0; i < other.number_of_children(); ++i) {
				if (other.child(i) == nullptr) {
					this->subtrees.append(move_cast(ref_cast(Pointer<AbstractTree<TYPE>>())));
				}
				else {
					this->subtrees.append(move_cast(ref_cast(other.child(i)->clone())));
				}
			}
			return;
		}

		template <template <typename> typename LIST_TYPE, typename TYPE>
		inline void ListStoredTree<LIST_TYPE, TYPE>::_cleanup_() {
			return;
		}

		template <template <typename> typename LIST_TYPE, typename TYPE>
		inline void ListStoredTree<LIST_TYPE, TYPE>::_super_move_(ListStoredTree<LIST_TYPE, TYPE>& other) {
			AbstractValuedTree<TYPE>::_move_(other);
			return;
		}

		template <template <typename> typename LIST_TYPE, typename TYPE>
		inline void ListStoredTree<LIST_TYPE, TYPE>::_super_copy_(const ListStoredTree<LIST_TYPE, TYPE>& other) {
			AbstractValuedTree<TYPE>::_copy_(other);
			return;
		}

		template <template <typename> typename LIST_TYPE, typename TYPE>
		inline void ListStoredTree<LIST_TYPE, TYPE>::_super_cleanup_() {
			AbstractValuedTree<TYPE>::_cleanup_();
			return;
		}

	}

}