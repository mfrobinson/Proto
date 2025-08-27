#pragma once
#include "Declarations/Data Structures/List/ArrayList.h"
#include "Memory Management/move_memory.h"

#define ARRAY_LIST_START_SIZE 10
#define ARRAY_LIST_GROWTH_FACTOR 2


namespace Proto {

	template <typename TYPE>
	ArrayList<TYPE>::ArrayList() : space_used(0), internal_array(ARRAY_LIST_START_SIZE) {
		return;
	}

	template <typename TYPE>
	ArrayList<TYPE>::ArrayList(ArrayList<TYPE>&& other) noexcept {
		this->_move_(other);
		return;
	}

	template <typename TYPE>
	ArrayList<TYPE>::ArrayList(const ArrayList<TYPE>& other) {
		this->_copy_(other);
		return;
	}

	template <typename TYPE>
	ArrayList<TYPE>& ArrayList<TYPE>::operator=(ArrayList<TYPE>&& other) noexcept {
		if (&other != this) {
			this->_cleanup_();
			this->_move_(other);
		}
		return *this;
	}

	template <typename TYPE>
	ArrayList<TYPE>& ArrayList<TYPE>::operator=(const ArrayList<TYPE>& other) {
		if (&other != this) {
			this->_cleanup_();
			this->_copy_(other);
		}
		return *this;
	}

	template <typename TYPE>
	ArrayList<TYPE>::~ArrayList() noexcept {
		this->_cleanup_();
		return;
	}

	template <typename TYPE>
	void ArrayList<TYPE>::append(TYPE value) {
		this->upsize_internal_array_if_needed();
		this->internal_array[this->space_used++] = move_cast(value);
		return;
	}

	template <typename TYPE>
	void ArrayList<TYPE>::insert(const size_t index, TYPE value) {
		if (index > this->space_used) {
			throw std::runtime_error("Index is out of bounds!");
		}
		this->upsize_internal_array_if_needed();
		for (size_t i = this->space_used; i > index; --i) {
			this->internal_array[i] = move_cast(this->internal_array[i - 1]);
		}
		this->internal_array[index] = move_cast(value);
		return;
	}

	template <typename TYPE>
	TYPE& ArrayList<TYPE>::get(const size_t index) {
		if (index >= this->space_used) {
			throw std::runtime_error("Index is out of bounds!");
		}
		return this->internal_array[index];
	}

	template <typename TYPE>
	const TYPE& ArrayList<TYPE>::get(const size_t index) const {
		if (index >= this->space_used) {
			throw std::runtime_error("Index is out of bounds!");
		}
		return this->internal_array[index];
	}

	template <typename TYPE>
	TYPE ArrayList<TYPE>::pop(const size_t index) {
		if (index >= this->space_used) {
			throw std::runtime_error("Index is out of bounds!");
		}
		TYPE result(move_cast(this->internal_array[index]));
		--this->space_used;
		move_memory<TYPE>(&this->internal_array[index + 1], &this->internal_array[index], this->space_used - index);
		return result;
	}

	template <typename TYPE>
	size_t ArrayList<TYPE>::length() const noexcept {
		return this->space_used;
	}

	template <typename TYPE>
	inline void ArrayList<TYPE>::_move_(ArrayList<TYPE>& other) noexcept {
		this->internal_array = move_cast(other.internal_array);
		this->space_used = other.space_used;
		other.space_used = 0;
		return;
	}

	template <typename TYPE>
	inline void ArrayList<TYPE>::_copy_(const ArrayList<TYPE>& other) {
		this->internal_array = other.internal_array;
		this->space_used = other.space_used;
		return;
	}

	template <typename TYPE>
	inline void ArrayList<TYPE>::_cleanup_() noexcept {
		return;
	}

	template <typename TYPE>
	inline void ArrayList<TYPE>::upsize_internal_array_if_needed() {
		if (this->space_used == this->internal_array.length()) {
			this->upsize_internal_array();
		}
		return;
	}

	template <typename TYPE>
	inline void ArrayList<TYPE>::upsize_internal_array() {
		Array<TYPE> extended_array(this->internal_array.length() * ARRAY_LIST_GROWTH_FACTOR);
		move_memory<TYPE>(this->internal_array, extended_array, this->internal_array.length());
		this->internal_array = move_cast(extended_array);
		return;
	}

}