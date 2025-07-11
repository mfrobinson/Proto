#pragma once
#include "Declarations/Memory Management/Pointers/Array.h"
#include <stdexcept>


namespace Proto {

	template <typename TYPE>
	Array<TYPE>::Array() : ArrayPointer<TYPE>(), size(0) {
		return;
	}

	template <typename TYPE>
	Array<TYPE>::Array(Array<TYPE>&& other) {
		this->_move_(other);
		return;
	}

	template <typename TYPE>
	Array<TYPE>::Array(const Array<TYPE>& other) {
		this->_copy_(other);
		return;
	}

	template <typename TYPE>
	Array<TYPE>& Array<TYPE>::operator=(Array<TYPE>&& other) {
		if (&other != this) {
			this->_super_cleanup_();
			this->_cleanup_();
			this->_move_(other);
		}
		return *this;
	}

	template <typename TYPE>
	Array<TYPE>& Array<TYPE>::operator=(const Array<TYPE>& other) {
		if (&other != this) {
			this->_super_cleanup_();
			this->_cleanup_();
			this->_copy_(other);
		}
		return *this;
	}

	template <typename TYPE>
	Array<TYPE>::~Array() {
		this->_cleanup_();
		return;
	}

	template <typename TYPE>
	template <typename...TYPES> requires std::conjunction<std::is_same<TYPE, TYPES>...>::value
	Array<TYPE>::Array(const TYPES&...values) : ArrayPointer<TYPE>(values...), size(sizeof...(values)) {
		return;
	}

	template <typename TYPE>
	template <typename...TYPES> requires std::conjunction<std::is_same<TYPE, TYPES>...>::value
	Array<TYPE>::Array(TYPES&&...values) : ArrayPointer<TYPE>(values...), size(sizeof...(values)) {
		return;
	}

	template <typename TYPE>
	Array<TYPE>::Array(const size_t number_of_values) : ArrayPointer<TYPE>(number_of_values), size(number_of_values) {
		return;
	}

	template <typename TYPE>
	Array<TYPE>::Array(const size_t number_of_values, const TYPE* values) : ArrayPointer<TYPE>(number_of_values, values), size(number_of_values) {
		return;
	}

	template <typename TYPE>
	TYPE& Array<TYPE>::operator[](const size_t index) {
		return this->access_index(index);
	}

	template <typename TYPE>
	const TYPE& Array<TYPE>::operator[](const size_t index) const {
		return this->access_index(index);
	}

	template <typename TYPE>
	size_t Array<TYPE>::length() const {
		return this->size;
	}

	template <typename TYPE>
	inline void Array<TYPE>::_move_(Array<TYPE>& other) {
		this->_super_move_(other);
		this->size = other.size;
		other.size = 0;
		return;
	}

	template <typename TYPE>
	inline void Array<TYPE>::_copy_(const Array<TYPE>& other) {
		this->_super_copy_(other);
		this->size = other.size;
		return;
	}

	template <typename TYPE>
	inline void Array<TYPE>::_cleanup_() {
		this->size = 0;
		return;
	}

	template <typename TYPE>
	inline void Array<TYPE>::_super_move_(Array<TYPE>& other) {
		ArrayPointer<TYPE>::_move_((ArrayPointer<TYPE>&)other);
		return;
	}

	template <typename TYPE>
	inline void Array<TYPE>::_super_copy_(const Array<TYPE>& other) {
		ArrayPointer<TYPE>::_copy_((const ArrayPointer<TYPE>&)other, other.size);
		return;
	}

	template <typename TYPE>
	inline void Array<TYPE>::_super_cleanup_() {
		ArrayPointer<TYPE>::_cleanup_();
		return;
	}

	template <typename TYPE>
	inline TYPE& Array<TYPE>::access_index(const size_t index) const {
		if (index >= this->size) {
			throw std::runtime_error("Supplied index is out of bounds!");
		}
		return (TYPE&)(ArrayPointer<TYPE>::operator[](index));
	}

	template <typename TYPE>
	std::ostream& operator<<(std::ostream& os, const Array<TYPE>& arr) {
		os << '[';
		for (size_t i = 0; i < arr.length(); ++i) {
			os << arr[i];
			if (i + 1 < arr.length()) {
				os << ',';
			}
		}
		os << ']';
		return os;
	}

}