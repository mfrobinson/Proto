#pragma once
#include "Declarations/Memory Management/Pointers/LazyArray.h"
#include <stdexcept>


namespace Proto {

	template <typename TYPE>
	LazyArray<TYPE>::LazyArray() : size(0) {
		return;
	}

	template <typename TYPE>
	LazyArray<TYPE>::LazyArray(LazyArray<TYPE>&& other) {
		this->_move_(other);
		return;
	}

	template <typename TYPE>
	LazyArray<TYPE>::LazyArray(const LazyArray<TYPE>& other) {
		this->_copy_(other);
		return;
	}

	template <typename TYPE>
	LazyArray<TYPE>& LazyArray<TYPE>::operator=(LazyArray<TYPE>&& other) {
		if (&other != this) {
			this->_super_cleanup_();
			this->_cleanup_();
			this->_move_(other);
		}
		return *this;
	}

	template <typename TYPE>
	LazyArray<TYPE>& LazyArray<TYPE>::operator=(const LazyArray<TYPE>& other) {
		if (&other != this) {
			this->_super_cleanup_();
			this->_cleanup_();
			this->_copy_(other);
		}
		return *this;
	}

	template <typename TYPE>
	LazyArray<TYPE>::~LazyArray() {
		this->_cleanup_();
		return;
	}

	template <typename TYPE>
	template <typename...TYPES>
	LazyArray<TYPE>::LazyArray(TYPES&&...values) : size(sizeof...(values)), ArrayPointer<Optional<TYPE>>(Optional<TYPE>(values)...) {
		return;
	}

	template <typename TYPE>
	template <typename...TYPES>
	LazyArray<TYPE>::LazyArray(const TYPES&...values) : size(sizeof...(values)), ArrayPointer<Optional<TYPE>>(Optional<TYPE>(values)...) {
		return;
	}
	
	template <typename TYPE>
	LazyArray<TYPE>::LazyArray(const size_t number_of_values) : size(sizeof...(values)), ArrayPointer<Optional<TYPE>>(sizeof...(values)) {
		return;
	}
	
	template <typename TYPE>
	LazyArray<TYPE>::LazyArray(const size_t number_of_values, const TYPE& value) : size(number_of_values), ArrayPointer<Optional<TYPE>>(number_of_values, value) {
		return;
	}
	
	template <typename TYPE>
	LazyArray<TYPE>::LazyArray(const size_t number_of_values, const TYPE* values) : size(number_of_values), ArrayPointer<Optional<TYPE>>(number_of_values, values) {
		return;
	}

	template <typename TYPE>
	size_t LazyArray<TYPE>::length() const {
		return this->size;
	}


	template <typename TYPE>
	Optional<TYPE>& LazyArray<TYPE>::operator[](const size_t index) {
		return this->access_index(index);
	}

	template <typename TYPE>
	const Optional<TYPE>& LazyArray<TYPE>::operator[](const size_t index) const {
		return this->access_index(index);
	}

	template <typename TYPE>
	inline void LazyArray<TYPE>::_move_(LazyArray<TYPE>& other) {
		this->_super_move_(other);
		this->size = other.size;
		other.size = 0;
		return;
	}

	template <typename TYPE>
	inline void LazyArray<TYPE>::_copy_(const LazyArray<TYPE>& other) {
		this->_super_copy_(other);
		this->size = other.size;
		return;
	}

	template <typename TYPE>
	inline void LazyArray<TYPE>::_cleanup_() {
		return;
	}

	template <typename TYPE>
	inline void LazyArray<TYPE>::_super_move_(LazyArray<TYPE>& other) {
		ArrayPointer<Optional<TYPE>>::_move_((ArrayPointer<Optional<TYPE>>&)other);
		return;
	}

	template <typename TYPE>
	inline void LazyArray<TYPE>::_super_copy_(const LazyArray<TYPE>& other) {
		ArrayPointer<Optional<TYPE>>::_move_((ArrayPointer<Optional<TYPE>>&)other, other.size);
	}

	template <typename TYPE>
	inline void LazyArray<TYPE>::_super_cleanup_() {
		ArrayPointer<Optional<TYPE>>::_cleanup_();
		return;
	}

	template <typename TYPE>
	inline Optional<TYPE>& LazyArray<TYPE>::access_index(const size_t index) const {
		if (index >= this->size) {
			throw std::runtime_error("Supplied index is out of bounds!");
		}
		return (Optional<TYPE>&)(ArrayPointer<Optional<TYPE>>::operator[](index));
	}

}