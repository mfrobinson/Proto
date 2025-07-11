#pragma once
#include "Declarations/Data Structures/Tree/Polymorphic/AbstractValuedTree.h"
#include "Cast/move_cast.h"


namespace Proto {

	namespace Polymorphic {

		template <typename TYPE>
		AbstractValuedTree<TYPE>::AbstractValuedTree() {
			return;
		}

		template <typename TYPE>
		AbstractValuedTree<TYPE>::AbstractValuedTree(AbstractValuedTree<TYPE>&& other) : root_value(move_cast(other.root_value)) {
			return;
		}

		template <typename TYPE>
		AbstractValuedTree<TYPE>::AbstractValuedTree(const AbstractValuedTree<TYPE>& other) : root_value(other.root_value) {
			return;
		}

		template <typename TYPE>
		AbstractValuedTree<TYPE>& AbstractValuedTree<TYPE>::operator=(AbstractValuedTree<TYPE>&& other) {
			if (&other != this) {
				this->_cleanup_();
				this->_move_(other);
			}
			return *this;
		}

		template <typename TYPE>
		AbstractValuedTree<TYPE>& AbstractValuedTree<TYPE>::operator=(const AbstractValuedTree<TYPE>& other) {
			if (&other != this) {
				this->_cleanup_();
				this->_copy_(other);
			}
			return *this;
		}

		template <typename TYPE>
		AbstractValuedTree<TYPE>::~AbstractValuedTree() {
			this->_cleanup_();
		}

		template <typename TYPE>
		AbstractValuedTree<TYPE>::AbstractValuedTree(TYPE root_value) : root_value(move_cast(root_value)) {
			return;
		}

		template <typename TYPE>
		TYPE& AbstractValuedTree<TYPE>::value() {
			return this->root_value;
		}

		template <typename TYPE>
		const TYPE& AbstractValuedTree<TYPE>::value() const {
			return this->root_value;
		}
		
		template <typename TYPE>
		inline void AbstractValuedTree<TYPE>::_move_(AbstractValuedTree<TYPE>& other) {
			this->root_value = move_cast(other);
			return;
		}

		template <typename TYPE>
		inline void AbstractValuedTree<TYPE>::_copy_(const AbstractValuedTree<TYPE>& other) {
			this->root_value = other;
			return;
		}

		template <typename TYPE>
		inline void AbstractValuedTree<TYPE>::_cleanup_() {
			return;
		}

	}

}