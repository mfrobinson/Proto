#pragma once
#include "Declarations/Data Structures/List/LinkedList.h"
#include "Memory Management/move_memory.h"
#include "Cast/move_cast.h"
#include "Cast/ref_cast.h"


namespace Proto {

	template <typename TYPE>
	LinkedList<TYPE>::LinkedList() : number_of_nodes(0), last(nullptr) {
		return;
	}

	template <typename TYPE>
	LinkedList<TYPE>::LinkedList(LinkedList<TYPE>&& other) noexcept {
		this->_move_(other);
		return;
	}

	template <typename TYPE>
	LinkedList<TYPE>::LinkedList(const LinkedList<TYPE>& other) {
		this->_copy_(other);
		return;
	}

	template <typename TYPE>
	LinkedList<TYPE>& LinkedList<TYPE>::operator=(LinkedList<TYPE>&& other) noexcept {
		if (&other != this) {
			this->_cleanup_();
			this->_move_(other);
		}
		return *this;
	}

	template <typename TYPE>
	LinkedList<TYPE>& LinkedList<TYPE>::operator=(const LinkedList<TYPE>& other) {
		if (&other != this) {
			this->_cleanup_();
			this->_copy_(other);
		}
		return *this;
	}

	template <typename TYPE>
	LinkedList<TYPE>::~LinkedList() noexcept {
		this->_cleanup_();
		return;
	}

	template <typename TYPE>
	void LinkedList<TYPE>::append(TYPE value) {
		Pointer<Node> node_to_append(Node{ move_cast(value) });
		if (this->first == nullptr) {
			this->first = move_cast(node_to_append);
			this->last = this->first;
		}
		else {
			this->last->next = move_cast(node_to_append);
			this->last = this->last->next;
		}
		++this->number_of_nodes;
		return;
	}

	template <typename TYPE>
	void LinkedList<TYPE>::insert(const size_t index, TYPE value) {
		if (index > this->number_of_nodes) {
			throw std::runtime_error("Index is out of bounds!");
		}
		Pointer<Node>* target = &this->first;
		for (size_t i = 0; i < index; ++i) {
			target = &((*target)->next);
		}
		Pointer<Node> replacement_node(Node{ move_cast(value), move_cast(*target) });
		*target = move_cast(replacement_node);
		if (index == this->number_of_nodes) {
			this->last = *target;
		}
		++this->number_of_nodes;
		return;
	}

	template <typename TYPE>
	TYPE& LinkedList<TYPE>::get(const size_t index) {
		if (index >= this->number_of_nodes) {
			throw std::runtime_error("Index is out of bounds!");
		}
		return ref_cast(this->_access_index_(index));
	}

	template <typename TYPE>
	const TYPE& LinkedList<TYPE>::get(const size_t index) const {
		if (index >= this->number_of_nodes) {
			throw std::runtime_error("Index is out of bounds!");
		}
		return this->_access_index_(index);
	}

	template <typename TYPE>
	TYPE LinkedList<TYPE>::pop(const size_t index) {
		if (index >= this->number_of_nodes) {
			throw std::runtime_error("Index is out of bounds!");
		}
		Node* previous = nullptr;
		Pointer<Node>* target = &this->first;
		for (size_t i = 0; i < index; ++i) {
			previous = *target;
			target = &((*target)->next);
		}
		Pointer<Node> after = move_cast((*target)->next);
		*target = move_cast(after);
		--this->number_of_nodes;
		if (index == this->number_of_nodes) {
			this->last = previous;
		}
		return TYPE();
	}

	template <typename TYPE>
	size_t LinkedList<TYPE>::length() const noexcept {
		return this->number_of_nodes;
	}

	template <typename TYPE>
	inline void LinkedList<TYPE>::_move_(LinkedList<TYPE>& other) noexcept {
		this->first = move_cast(other.first);
		this->space_used = other.space_used;
		this->last = other.last;
		other.space_used = 0;
		other.last = nullptr;
		return;
	}

	template <typename TYPE>
	inline void LinkedList<TYPE>::_copy_(const LinkedList<TYPE>& other) {
		this->first = other.first;
		this->number_of_nodes = other.number_of_nodes;
		this->last = this->first;
		for (size_t i = 0; i < this->number_of_nodes; ++i) {
			this->last = this->last->next;
		}
		return;
	}

	template <typename TYPE>
	inline void LinkedList<TYPE>::_cleanup_() noexcept {
		return;
	}

	template <typename TYPE>
	inline const TYPE& LinkedList<TYPE>::_access_index_(const size_t index) const {
		const Node* current = this->first;
		for (size_t i = 0; i < index; ++i) {
			current = current->next;
		}
		return current->value;
	}

}