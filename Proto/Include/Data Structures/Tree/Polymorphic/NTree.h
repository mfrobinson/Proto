#pragma once
#include "Declarations/Data Structures/Tree/Polymorphic/NTree.h"
#include "Cast/move_cast.h"
#include "Memory Management/Pointers/PolymorphicPointer.h"
#include "Cast/ref_cast.h"


namespace Proto {

	namespace Polymorphic {

		template <size_t N, typename STORED_TYPE>
		NTree<N, STORED_TYPE>::NTree() {
			return;
		}

		template <size_t N, typename STORED_TYPE>
		NTree<N, STORED_TYPE>::NTree(NTree<N, STORED_TYPE>&& other) : ValuedTree<size_t, STORED_TYPE>(move_cast(other)) {
			this->_this_move_(other);
			return;
		}

		template <size_t N, typename STORED_TYPE>
		NTree<N, STORED_TYPE>::NTree(const NTree<N, STORED_TYPE>& other) : ValuedTree<size_t, STORED_TYPE>(other) {
			this->_this_copy_(other);
			return;
		}
		
		template <size_t N, typename STORED_TYPE>
		NTree<N, STORED_TYPE>& NTree<N, STORED_TYPE>::operator=(NTree<N, STORED_TYPE>&& other) {
			if (&other != this) {
				this->_cleanup_();
				this->_super_cleanup_();
				this->_move_(other);
			}
			return *this;
		}
		
		template <size_t N, typename STORED_TYPE>
		NTree<N, STORED_TYPE>& NTree<N, STORED_TYPE>::operator=(const NTree<N, STORED_TYPE>& other) {
			if (&other != this) {
				this->_cleanup_();
				this->_super_cleanup_();
				this->_copy_(other);
			}
			return *this;
		}

		template <size_t N, typename STORED_TYPE>
		NTree<N, STORED_TYPE>::~NTree() {
			this->_cleanup_();
			return;
		}

		template <size_t N, typename STORED_TYPE>
		NTree<N, STORED_TYPE>::NTree(STORED_TYPE root) : ValuedTree<size_t, STORED_TYPE>(move_cast(root)) {
			return;
		}

		template <size_t N, typename STORED_TYPE>
		void NTree<N, STORED_TYPE>::add(Pointer<AbstractTree<size_t, STORED_TYPE>>& subtree) {

		}
		template <size_t N, typename STORED_TYPE>
		void NTree<N, STORED_TYPE>::insert(size_t position, Pointer<AbstractTree<size_t, STORED_TYPE>>& subtree) {

		}
		template <size_t N, typename STORED_TYPE>
		void NTree<N, STORED_TYPE>::remove(const size_t& position) {

		}

		template <size_t N, typename STORED_TYPE>
		void NTree<N, STORED_TYPE>::children(AbstractDictionary<size_t, AbstractTree<size_t, STORED_TYPE>*>* storage_solution) {
			this->retrieve_children_to_dictionary(storage_solution);
			return;
		}

		template <size_t N, typename STORED_TYPE>
		void NTree<N, STORED_TYPE>::children(AbstractDictionary<size_t, const AbstractTree<size_t, STORED_TYPE>*>* storage_solution) const {
			this->retrieve_children_to_dictionary(storage_solution);
			return;
		}

		template <size_t N, typename STORED_TYPE>
		AbstractTree<size_t, STORED_TYPE>* NTree<N, STORED_TYPE>::child(const size_t& position) {
			return this->retrieve_child(position);
		}

		template <size_t N, typename STORED_TYPE>
		const AbstractTree<size_t, STORED_TYPE>* NTree<N, STORED_TYPE>::child(const size_t& position) const {
			return this->retrieve_child(position);
		}

		template <size_t N, typename STORED_TYPE>
		size_t NTree<N, STORED_TYPE>::number_of_children() const noexcept {
			size_t result = 0;
			for (size_t i = 0; i < N; ++i) {
				if (this->child_trees[i] != nullptr) {
					++result;
				}
			}
			return result;
		}

		template <size_t N, typename STORED_TYPE>
		Pointer<AbstractTree<size_t, STORED_TYPE>> NTree<N, STORED_TYPE>::clone() const {
			return PolymorphicPointer<AbstractTree<size_t, STORED_TYPE>>(NTree<N, STORED_TYPE>(*this));
		}

		template <size_t N, typename STORED_TYPE>
		inline void NTree<N, STORED_TYPE>::_move_(NTree<N, STORED_TYPE>& other) {
			this->_super_move_(other);
			this->_move_(other);
			return;
		}

		template <size_t N, typename STORED_TYPE>
		inline void NTree<N, STORED_TYPE>::_copy_(const NTree<N, STORED_TYPE>& other) {
			this->_super_copy_(other);
			this->_copy_(other);
			return;
		}

		template <size_t N, typename STORED_TYPE>
		inline void NTree<N, STORED_TYPE>::_cleanup_() {
			return;
		}

		template <size_t N, typename STORED_TYPE>
		inline void NTree<N, STORED_TYPE>::_this_move_(NTree<N, STORED_TYPE>& other) {
			this->child_trees = move_cast(other.child_trees);
			return;
		}

		template <size_t N, typename STORED_TYPE>
		inline void NTree<N, STORED_TYPE>::_this_copy_(const NTree<N, STORED_TYPE>& other) {
			this->child_trees = other.child_trees;
			return;
		}

		template <size_t N, typename STORED_TYPE>
		inline void NTree<N, STORED_TYPE>::_super_move_(NTree<N, STORED_TYPE>& other) {
			ValuedTree<size_t, STORED_TYPE>::_move_(other);
			return;
		}

		template <size_t N, typename STORED_TYPE>
		inline void NTree<N, STORED_TYPE>::_super_copy_(const NTree<N, STORED_TYPE>& other) {
			ValuedTree<size_t, STORED_TYPE>::_copy_(other);
			return;
		}

		template <size_t N, typename STORED_TYPE>
		inline void NTree<N, STORED_TYPE>::_super_cleanup_() {
			ValuedTree<size_t, STORED_TYPE>::_cleanup_();
			return;
		}

		template <size_t N, typename STORED_TYPE>
		inline AbstractTree<size_t, STORED_TYPE>* NTree<N, STORED_TYPE>::retrieve_child(const size_t& position) const {
			return ref_cast(this->child_trees[position]);
		}

		template <size_t N, typename STORED_TYPE>
		template <typename CHILD_TYPE>
		inline void NTree<N, STORED_TYPE>::retrieve_children_to_dictionary(AbstractDictionary<size_t, CHILD_TYPE>* storage_solution) const {
			for (size_t i = 0; i < N; ++i) {
				storage_solution->set(i, ref_cast(this->child_trees[i]));
			}
			return;
		}

	}

}