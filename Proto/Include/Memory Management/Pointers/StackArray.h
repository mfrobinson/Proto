#pragma once
#include "Declarations/Memory Management/Pointers/StackArray.h"
#include "Memory Management/move_memory.h"
#include "Memory Management/copy_memory.h"
#include "Cast/ref_cast.h"


namespace Proto {

	template <size_t N, typename TYPE>
	StackArray<N, TYPE>::StackArray() {
		return;
	}

	template <size_t N, typename TYPE>
	StackArray<N, TYPE>::StackArray(StackArray<N, TYPE>&& other) {
		this->_move_(other);
		return;
	}

	template <size_t N, typename TYPE>
	StackArray<N, TYPE>::StackArray(const StackArray<N, TYPE>& other) {
		this->_copy_(other);
		return;
	}

	template <size_t N, typename TYPE>
	StackArray<N, TYPE>& StackArray<N, TYPE>::operator=(StackArray<N, TYPE>&& other) {
		if (&other != this) {
			this->_cleanup_();
			this->_move_(other);
		}
		return *this;
	}

	template <size_t N, typename TYPE>
	StackArray<N, TYPE>& StackArray<N, TYPE>::operator=(const StackArray<N, TYPE>& other) {
		if (&other != this) {
			this->_cleanup_();
			this->_copy_(other);
		}
		return *this;
	}

	template <size_t N, typename TYPE>
	StackArray<N, TYPE>::~StackArray() {
		this->_cleanup_();
		return;
	}

	template <size_t N, typename TYPE>
	TYPE& StackArray<N, TYPE>::operator[](const size_t index) {
		return this->access_index(index);
	}

	template <size_t N, typename TYPE>
	const TYPE& StackArray<N, TYPE>::operator[](const size_t index) const {
		return this->access_index(index);
	}

	template <size_t N, typename TYPE>
	StackArray<N, TYPE>::operator TYPE* () {
		return this->access_pointer();
	}

	template <size_t N, typename TYPE>
	StackArray<N, TYPE>::operator const TYPE* () const {
		return this->access_pointer();
	}

	template <size_t N, typename TYPE>
	inline void StackArray<N, TYPE>::_move_(StackArray<N, TYPE>& other) {
		move_memory(other.internal_array, this->internal_array, N);
		return;
	}

	template <size_t N, typename TYPE>
	inline void StackArray<N, TYPE>::_copy_(const StackArray<N, TYPE>& other) {
		copy_memory(other.internal_array, this->internal_array, N);
		return;
	}

	template <size_t N, typename TYPE>
	inline void StackArray<N, TYPE>::_cleanup_() {
		return;
	}

	template <size_t N, typename TYPE>
	inline TYPE* StackArray<N, TYPE>::access_pointer() const {
		return ref_cast(this->internal_array);
	}

	template <size_t N, typename TYPE>
	inline TYPE& StackArray<N, TYPE>::access_index(const size_t index) const {
		if (index >= N) {
			throw std::runtime_error("Index is out of bounds to access StackArray!");
		}
		return ref_cast(this->internal_array[index]);
	}

}