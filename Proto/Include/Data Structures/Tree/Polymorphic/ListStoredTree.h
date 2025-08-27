#pragma once
#include "Declarations/Data Structures/Tree/Polymorphic/ListStoredTree.h"
#include "Cast/move_cast.h"
#include "Memory Management/Pointers/PolymorphicPointer.h"
#include "Data Structures/Dictionary/ArrayDictionary.h"
#include "Cast/ref_cast.h"


namespace Proto {

	namespace Polymorphic {

		template <template <typename> typename LIST_TYPE, typename STORED_TYPE>
		ListStoredTree<LIST_TYPE, STORED_TYPE>::ListStoredTree() {
			return;
		}
		
		template <template <typename> typename LIST_TYPE, typename STORED_TYPE>
		ListStoredTree<LIST_TYPE, STORED_TYPE>::ListStoredTree(ListStoredTree<LIST_TYPE, STORED_TYPE>&& other) : ValuedTree<size_t, STORED_TYPE>((ValuedTree<size_t, STORED_TYPE>&&)other) {
			this->_this_move_(other);
			return;
		}
		
		template <template <typename> typename LIST_TYPE, typename STORED_TYPE>
		ListStoredTree<LIST_TYPE, STORED_TYPE>::ListStoredTree(const ListStoredTree<LIST_TYPE, STORED_TYPE>& other) : ValuedTree<size_t, STORED_TYPE>((const ValuedTree<size_t, STORED_TYPE>&)other) {
			this->_this_copy_(other);
			return;
		}
		
		template <template <typename> typename LIST_TYPE, typename STORED_TYPE>
		ListStoredTree<LIST_TYPE, STORED_TYPE>& ListStoredTree<LIST_TYPE, STORED_TYPE>::operator=(ListStoredTree<LIST_TYPE, STORED_TYPE>&& other) {
			if (&other != this) {
				this->_super_cleanup_();
				this->_cleanup_();
				this->_move_(other);
			}
			return *this;
		}
		
		template <template <typename> typename LIST_TYPE, typename STORED_TYPE>
		ListStoredTree<LIST_TYPE, STORED_TYPE>& ListStoredTree<LIST_TYPE, STORED_TYPE>::operator=(const ListStoredTree<LIST_TYPE, STORED_TYPE>& other) {
			if (&other != this) {
				this->_super_cleanup_();
				this->_cleanup_();
				this->_copy_(other);
			}
			return *this;
		}

		template <template <typename> typename LIST_TYPE, typename STORED_TYPE>
		ListStoredTree<LIST_TYPE, STORED_TYPE>::~ListStoredTree() {
			return;
		}

		template <template <typename> typename LIST_TYPE, typename STORED_TYPE>
		ListStoredTree<LIST_TYPE, STORED_TYPE>::ListStoredTree(STORED_TYPE root) : ValuedTree<size_t, STORED_TYPE>(move_cast(root)) {
			return;
		}

		template <template <typename> typename LIST_TYPE, typename STORED_TYPE>
		void ListStoredTree<LIST_TYPE, STORED_TYPE>::add(Pointer<AbstractTree<size_t, STORED_TYPE>>& subtree) {
			this->child_trees.append(move_cast(subtree));
			return;
		}

		template <template <typename> typename LIST_TYPE, typename STORED_TYPE>
		void ListStoredTree<LIST_TYPE, STORED_TYPE>::insert(size_t position, Pointer<AbstractTree<size_t, STORED_TYPE>>& subtree) {
			this->child_trees.insert(position, subtree);
			return;
		}

		template <template <typename> typename LIST_TYPE, typename STORED_TYPE>
		void ListStoredTree<LIST_TYPE, STORED_TYPE>::remove(const size_t& position) {
			this->child_trees.pop(position);
			return;
		}

		template <template <typename> typename LIST_TYPE, typename STORED_TYPE>
		void ListStoredTree<LIST_TYPE, STORED_TYPE>::children(AbstractDictionary<size_t, AbstractTree<size_t, STORED_TYPE>*>* storage_solution) {
			this->retrieve_children_to_dictionary(storage_solution);
			return;
		}

		template <template <typename> typename LIST_TYPE, typename STORED_TYPE>
		void ListStoredTree<LIST_TYPE, STORED_TYPE>::children(AbstractDictionary<size_t, const AbstractTree<size_t, STORED_TYPE>*>* storage_solution) const {
			this->retrieve_children_to_dictionary(storage_solution);
			return;
		}

		template <template <typename> typename LIST_TYPE, typename STORED_TYPE>
		AbstractTree<size_t, STORED_TYPE>* ListStoredTree<LIST_TYPE, STORED_TYPE>::child(const size_t& position) {
			return this->child_trees.get(position);
		}

		template <template <typename> typename LIST_TYPE, typename STORED_TYPE>
		const AbstractTree<size_t, STORED_TYPE>* ListStoredTree<LIST_TYPE, STORED_TYPE>::child(const size_t& position) const {
			return this->child_trees.get(position);
		}

		template <template <typename> typename LIST_TYPE, typename STORED_TYPE>
		size_t ListStoredTree<LIST_TYPE, STORED_TYPE>::number_of_children() const noexcept {
			return this->child_trees.length();
		}

		template <template <typename> typename LIST_TYPE, typename STORED_TYPE>
		Pointer<AbstractTree<size_t, STORED_TYPE>> ListStoredTree<LIST_TYPE, STORED_TYPE>::clone() const {
			return PolymorphicPointer<AbstractTree<size_t, STORED_TYPE>>(ListStoredTree<LIST_TYPE, STORED_TYPE>(*this));
		}

		template <template <typename> typename LIST_TYPE, typename STORED_TYPE>
		inline void ListStoredTree<LIST_TYPE, STORED_TYPE>::_move_(ListStoredTree<LIST_TYPE, STORED_TYPE>& other) {
			this->_super_move_(other);
			this->_this_move_(other);
			return;
		}

		template <template <typename> typename LIST_TYPE, typename STORED_TYPE>
		inline void ListStoredTree<LIST_TYPE, STORED_TYPE>::_copy_(const ListStoredTree<LIST_TYPE, STORED_TYPE>& other) {
			this->_super_copy_(other);
			this->_this_copy_(other);
			return;
		}

		template <template <typename> typename LIST_TYPE, typename STORED_TYPE>
		inline void ListStoredTree<LIST_TYPE, STORED_TYPE>::_cleanup_() {
			return;
		}

		template <template <typename> typename LIST_TYPE, typename STORED_TYPE>
		inline void ListStoredTree<LIST_TYPE, STORED_TYPE>::_this_move_(ListStoredTree<LIST_TYPE, STORED_TYPE>& other) {
			this->child_trees = move_cast(other.child_trees);
			return;
		}

		template <template <typename> typename LIST_TYPE, typename STORED_TYPE>
		inline void ListStoredTree<LIST_TYPE, STORED_TYPE>::_this_copy_(const ListStoredTree<LIST_TYPE, STORED_TYPE>& other) {
			this->child_trees = other.child_trees;
			return;
		}

		template <template <typename> typename LIST_TYPE, typename STORED_TYPE>
		inline void ListStoredTree<LIST_TYPE, STORED_TYPE>::_super_move_(ListStoredTree<LIST_TYPE, STORED_TYPE>& other) {
			ValuedTree<LIST_TYPE, STORED_TYPE>::_move_(other);
			return;
		}

		template <template <typename> typename LIST_TYPE, typename STORED_TYPE>
		inline void ListStoredTree<LIST_TYPE, STORED_TYPE>::_super_copy_(const ListStoredTree<LIST_TYPE, STORED_TYPE>& other) {
			ValuedTree<LIST_TYPE, STORED_TYPE>::_copy_(other);
			return;
		}

		template <template <typename> typename LIST_TYPE, typename STORED_TYPE>
		inline void ListStoredTree<LIST_TYPE, STORED_TYPE>::_super_cleanup_() {
			ValuedTree<LIST_TYPE, STORED_TYPE>::_cleanup_();
			return;
		}

		template <template <typename> typename LIST_TYPE, typename STORED_TYPE>
		template <typename CHILD_TYPE>
		inline void ListStoredTree<LIST_TYPE, STORED_TYPE>::retrieve_children_to_dictionary(AbstractDictionary<size_t, CHILD_TYPE>* storage_solution) const {
			for (size_t i = 0; i < this->child_trees.length(); ++i) {
				storage_solution->set(i, ref_cast(this->child_trees.get(i)));
			}
			return;
		}

	}

}