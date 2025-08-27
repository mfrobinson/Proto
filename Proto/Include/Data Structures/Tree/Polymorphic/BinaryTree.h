#pragma once
#include "Declarations/Data Structures/Tree/Polymorphic/BinaryTree.h"
#include "Cast/move_cast.h"
#include "Data Structures/Dictionary/ArrayDictionary.h"
#include "Memory Management/Pointers/PolymorphicPointer.h"
#include "Cast/ref_cast.h"


namespace Proto {

	namespace Polymorphic {

		template <typename STORED_TYPE>
		const size_t BinaryTree<STORED_TYPE>::LEFT = 0;

		template <typename STORED_TYPE>
		const size_t BinaryTree<STORED_TYPE>::RIGHT = 1;

		template <typename STORED_TYPE>
		BinaryTree<STORED_TYPE>::BinaryTree() {
			return;
		}

		template <typename STORED_TYPE>
		BinaryTree<STORED_TYPE>::BinaryTree(BinaryTree<STORED_TYPE>&& other) : ValuedTree<size_t, STORED_TYPE>(move_cast(other)) {
			this->_this_move_(other);
			return;
		}

		template <typename STORED_TYPE>
		BinaryTree<STORED_TYPE>::BinaryTree(const BinaryTree<STORED_TYPE>& other) : ValuedTree<size_t, STORED_TYPE>(other) {
			this->_this_copy_(other);
			return;
		}

		template <typename STORED_TYPE>
		BinaryTree<STORED_TYPE>& BinaryTree<STORED_TYPE>::operator=(BinaryTree<STORED_TYPE>&& other) {
			if (&other != this) {
				this->_cleanup_();
				this->_super_cleanup_();
				this->_move_(other);
			}
			return *this;
		}

		template <typename STORED_TYPE>
		BinaryTree<STORED_TYPE>& BinaryTree<STORED_TYPE>::operator=(const BinaryTree<STORED_TYPE>& other) {
			if (&other != this) {
				this->_cleanup_();
				this->_super_cleanup_();
				this->_copy_(other);
			}
			return *this;
		}

		template <typename STORED_TYPE>
		BinaryTree<STORED_TYPE>::~BinaryTree() {
			this->_cleanup_();
			return;
		}

		template <typename STORED_TYPE>
		BinaryTree<STORED_TYPE>::BinaryTree(STORED_TYPE root) : ValuedTree<size_t, STORED_TYPE>(move_cast(root)) {
			return;
		}

		template <typename STORED_TYPE>
		void BinaryTree<STORED_TYPE>::add(Pointer<AbstractTree<size_t, STORED_TYPE>>& subtree) {
			if (this->left_child == nullptr) {
				this->left_child = move_cast(subtree);
			}
			else if (this->right_child == nullptr) {
				this->right_child = move_cast(subtree);
			}
			else if (this->left_child->height() <= this->right_child->height()) {
				this->left_child->add(subtree);
			}
			else {
				this->right_child->add(subtree);
			}
			return;
		}

		template <typename STORED_TYPE>
		void BinaryTree<STORED_TYPE>::insert(size_t position, Pointer<AbstractTree<size_t, STORED_TYPE>>& subtree) {
			switch (position) {
			case BinaryTree<STORED_TYPE>::LEFT:
				if (this->left_child == nullptr) {
					this->left_child = move_cast(subtree);
				}
				else {
					this->left_child->add(subtree);
				}
				break;
			case BinaryTree<STORED_TYPE>::RIGHT:
				if (this->right_child == nullptr) {
					this->right_child = move_cast(subtree);
				}
				else {
					this->right_child->add(subtree);
				}
				break;
			default:
				throw std::runtime_error("Position provided does not specify a valid location to insert a subtree!");
			}
			return;
		}

		template <typename STORED_TYPE>
		void BinaryTree<STORED_TYPE>::remove(const size_t& position) {
			switch (position) {
			case BinaryTree<STORED_TYPE>::LEFT:
				this->left_child = Pointer<AbstractTree<size_t, STORED_TYPE>>();
				break;
			case BinaryTree<STORED_TYPE>::RIGHT:
				this->right_child = Pointer<AbstractTree<size_t, STORED_TYPE>>();
				break;
			default:
				throw std::runtime_error("Position provided does not specify a valid location to remove a subtree!");
			}
			return;
		}

		template <typename STORED_TYPE>
		void BinaryTree<STORED_TYPE>::children(AbstractDictionary<size_t, AbstractTree<size_t, STORED_TYPE>*>* storage_solution) {
			if (this->left_child != nullptr) {
				storage_solution->set(BinaryTree<STORED_TYPE>::LEFT, this->left_child);
			}
			if (this->right_child != nullptr) {
				storage_solution->set(BinaryTree<STORED_TYPE>::RIGHT, this->right_child);
			}
			return;
		}

		template <typename STORED_TYPE>
		void BinaryTree<STORED_TYPE>::children(AbstractDictionary<size_t, const AbstractTree<size_t, STORED_TYPE>*>* storage_solution) const {
			if (this->left_child != nullptr) {
				storage_solution->set(BinaryTree<STORED_TYPE>::LEFT, this->left_child);
			}
			if (this->right_child != nullptr) {
				storage_solution->set(BinaryTree<STORED_TYPE>::RIGHT, this->right_child);
			}
			return;
		}

		template <typename STORED_TYPE>
		AbstractTree<size_t, STORED_TYPE>* BinaryTree<STORED_TYPE>::child(const size_t& position) {
			return this->retrieve_child(position);
		}

		template <typename STORED_TYPE>
		const AbstractTree<size_t, STORED_TYPE>* BinaryTree<STORED_TYPE>::child(const size_t& position) const {
			return this->retrieve_child(position);
		}

		template <typename STORED_TYPE>
		size_t BinaryTree<STORED_TYPE>::number_of_children() const noexcept {
			size_t children = 0;
			if (this->left_child != nullptr) {
				++children;
			}
			if (this->right_child != nullptr) {
				++children;
			}
			return children;
		}

		template <typename STORED_TYPE>
		Pointer<AbstractTree<size_t, STORED_TYPE>> BinaryTree<STORED_TYPE>::clone() const {
			return PolymorphicPointer<AbstractTree<size_t, STORED_TYPE>>(BinaryTree<STORED_TYPE>(*this));
		}

		template <typename STORED_TYPE>
		std::ostream& BinaryTree<STORED_TYPE>::visualise(std::ostream& os, const String& prefix) const {
			os << this->value() << "\n";
			if (this->left_child != nullptr) {
				os << prefix << "|-L-";
				this->left_child->visualise(os, prefix + "|   ");
			}
			if (this->right_child != nullptr) {
				os << prefix << "|-R-";
				this->right_child->visualise(os, prefix + "    ");
			}
			return os;
		}

		template <typename STORED_TYPE>
		inline void BinaryTree<STORED_TYPE>::_move_(BinaryTree<STORED_TYPE>& other) {
			this->_super_move_(other);
			this->_this_move_(other);
			return;
		}

		template <typename STORED_TYPE>
		inline void BinaryTree<STORED_TYPE>::_copy_(const BinaryTree<STORED_TYPE>& other) {
			this->_super_copy_(other);
			this->_this_copy_(other);
			return;
		}

		template <typename STORED_TYPE>
		inline void BinaryTree<STORED_TYPE>::_cleanup_() {
			return;
		}

		template <typename STORED_TYPE>
		inline void BinaryTree<STORED_TYPE>::_this_move_(BinaryTree<STORED_TYPE>& other) {
			this->left_child = move_cast(other.left_child);
			this->right_child = move_cast(other.right_child);
			return;
		}

		template <typename STORED_TYPE>
		inline void BinaryTree<STORED_TYPE>::_this_copy_(const BinaryTree<STORED_TYPE>& other) {
			this->left_child = other.left_child;
			this->right_child = other.right_child;
			return;
		}

		template <typename STORED_TYPE>
		inline void BinaryTree<STORED_TYPE>::_super_move_(BinaryTree<STORED_TYPE>& other) {
			ValuedTree<size_t, STORED_TYPE>::_move_(other);
			return;
		}

		template <typename STORED_TYPE>
		inline void BinaryTree<STORED_TYPE>::_super_copy_(const BinaryTree<STORED_TYPE>& other) {
			ValuedTree<size_t, STORED_TYPE>::_copy_(other);
			return;
		}

		template <typename STORED_TYPE>
		inline void BinaryTree<STORED_TYPE>::_super_cleanup_() {
			ValuedTree<size_t, STORED_TYPE>::_cleanup_();
			return;
		}

		template <typename STORED_TYPE>
		inline AbstractTree<size_t, STORED_TYPE>* BinaryTree<STORED_TYPE>::retrieve_child(const size_t& position) const {
			switch (position) {
			case BinaryTree<STORED_TYPE>::LEFT:
				return ref_cast(this->left_child);
			case BinaryTree<STORED_TYPE>::RIGHT:
				return ref_cast(this->right_child);
			default:
				break;
			}
			throw std::runtime_error("Position provided does not specify a valid location to retrieve a subtree!");
		}

	}

}