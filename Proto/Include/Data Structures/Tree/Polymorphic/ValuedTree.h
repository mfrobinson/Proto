#pragma once
#include "Declarations/Data Structures/Tree/Polymorphic/ValuedTree.h"
#include "Cast/move_cast.h"


namespace Proto {

	namespace Polymorphic {

		template <typename INDEX_TYPE, typename STORED_TYPE>
		ValuedTree<INDEX_TYPE, STORED_TYPE>::ValuedTree() {
			return;
		}

		template <typename INDEX_TYPE, typename STORED_TYPE>
		ValuedTree<INDEX_TYPE, STORED_TYPE>::ValuedTree(ValuedTree<INDEX_TYPE, STORED_TYPE>&& other) : root_value(move_cast(other.root_value)) {
			return;
		}

		template <typename INDEX_TYPE, typename STORED_TYPE>
		ValuedTree<INDEX_TYPE, STORED_TYPE>::ValuedTree(const ValuedTree<INDEX_TYPE, STORED_TYPE>& other) : root_value(other.root_value) {
			return;
		}

		template <typename INDEX_TYPE, typename STORED_TYPE>
		ValuedTree<INDEX_TYPE, STORED_TYPE>& ValuedTree<INDEX_TYPE, STORED_TYPE>::operator=(ValuedTree<INDEX_TYPE, STORED_TYPE>&& other) {
			if (&other != this) {
				this->_cleanup_();
				this->_move_(other);
			}
			return *this;
		}

		template <typename INDEX_TYPE, typename STORED_TYPE>
		ValuedTree<INDEX_TYPE, STORED_TYPE>& ValuedTree<INDEX_TYPE, STORED_TYPE>::operator=(const ValuedTree<INDEX_TYPE, STORED_TYPE>& other) {
			if (&other != this) {
				this->_cleanup_();
				this->_copy_(other);
			}
			return *this;
		}

		template <typename INDEX_TYPE, typename STORED_TYPE>
		ValuedTree<INDEX_TYPE, STORED_TYPE>::~ValuedTree() {
			this->_cleanup_();
			return;
		}

		template <typename INDEX_TYPE, typename STORED_TYPE>
		ValuedTree<INDEX_TYPE, STORED_TYPE>::ValuedTree(STORED_TYPE root) : root_value(move_cast(root)) {
			return;
		}

		template <typename INDEX_TYPE, typename STORED_TYPE>
		STORED_TYPE& ValuedTree<INDEX_TYPE, STORED_TYPE>::value() {
			return this->root_value;
		}

		template <typename INDEX_TYPE, typename STORED_TYPE>
		const STORED_TYPE& ValuedTree<INDEX_TYPE, STORED_TYPE>::value() const {
			return this->root_value;
		}

		template <typename INDEX_TYPE, typename STORED_TYPE>
		inline void ValuedTree<INDEX_TYPE, STORED_TYPE>::_move_(ValuedTree<INDEX_TYPE, STORED_TYPE>& other) {
			this->root_value = move_cast(other.root_value);
			return;
		}

		template <typename INDEX_TYPE, typename STORED_TYPE>
		inline void ValuedTree<INDEX_TYPE, STORED_TYPE>::_copy_(const ValuedTree<INDEX_TYPE, STORED_TYPE>& other) {
			this->root_value = other.root_value;
			return;
		}

		template <typename INDEX_TYPE, typename STORED_TYPE>
		inline void ValuedTree<INDEX_TYPE, STORED_TYPE>::_cleanup_() {
			return;
		}

	}

}