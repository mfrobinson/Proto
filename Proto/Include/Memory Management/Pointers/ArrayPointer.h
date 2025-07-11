#pragma once
#include "Declarations/Memory Management/Pointers/ArrayPointer.h"
#include "Memory Management/copy_memory.h"
#include "Memory Management/move_memory.h"
#include "Memory Management/set_memory.h"
#include "Cast/move_cast.h"
#include <memory>


namespace Proto {

	template <typename TYPE>
	ArrayPointer<TYPE>::ArrayPointer() : memory(nullptr) {
		return;
	}

	template <typename TYPE>
	ArrayPointer<TYPE>::ArrayPointer(ArrayPointer<TYPE>&& other) {
		this->_move_(other);
		return;
	}

	template <typename TYPE>
	ArrayPointer<TYPE>& ArrayPointer<TYPE>::operator=(ArrayPointer<TYPE>&& other) {
		if (&other != this) {
			this->_cleanup_();
			this->_move_(other);
		}
		return *this;
	}

	template <typename TYPE>
	ArrayPointer<TYPE>::~ArrayPointer() {
		this->_cleanup_();
		return;
	}

	template <typename TYPE>
	template <typename...TYPES>
	ArrayPointer<TYPE>::ArrayPointer(TYPES&&...values) {
		if (sizeof...(values) != 0) {
			this->memory = new TYPE[sizeof...(values)](move_cast(values)...);
		}
		else {
			this->memory = nullptr;
		}
		return;
	}

	template <typename TYPE>
	template <typename...TYPES>
	ArrayPointer<TYPE>::ArrayPointer(const TYPES&...values) {
		if (sizeof...(values) != 0) {
			this->memory = new TYPE[sizeof...(values)](values...);
		}
		else {
			this->memory = nullptr;
		}
		return;
	}

	template <typename TYPE>
	ArrayPointer<TYPE>::ArrayPointer(const size_t number_of_values, const TYPE& value) {
		if (number_of_values == 0) {
			this->memory = nullptr;
		}
		this->memory = new TYPE[number_of_values];
		set_memory(this->memory, value, number_of_values);
		return;
	}

	template <typename TYPE>
	ArrayPointer<TYPE>::ArrayPointer(const size_t number_of_values) {
		if (number_of_values == 0) {
			this->memory = nullptr;
			return;
		}
		this->memory = new TYPE[number_of_values];
		return;
	}

	template <typename TYPE>
	ArrayPointer<TYPE>::ArrayPointer(const size_t number_of_values, const TYPE* values) {
		if (number_of_values == 0) {
			this->memory = nullptr;
			return;
		}
		this->memory = new TYPE[number_of_values];
		copy_memory(values, this->memory, number_of_values);
		return;
		/*
		// Allocate
		this->memory = (TYPE*)(::operator new[](sizeof(TYPE)* number_of_values));
		// Initialise
		for (size_t i = 0; i < number_of_values; ++i) {
			new (&this->memory[i]) TYPE(values[i]);
		}
		return;*/
	}

	template <typename TYPE>
	ArrayPointer<TYPE>::operator TYPE* () {
		return this->memory;
	}

	template <typename TYPE>
	ArrayPointer<TYPE>::operator const TYPE* () const {
		return this->memory;
	}

	template <typename TYPE>
	TYPE& ArrayPointer<TYPE>::operator[](const size_t index) {
		return this->memory[index];
	}

	template <typename TYPE>
	const TYPE& ArrayPointer<TYPE>::operator[](const size_t index) const {
		return this->memory[index];
	}

	template <typename TYPE>
	inline void ArrayPointer<TYPE>::_move_(ArrayPointer<TYPE>& other) {
		this->memory = other.memory;
		other.memory = nullptr;
		return;
	}

	template <typename TYPE>
	inline void ArrayPointer<TYPE>::_copy_(const ArrayPointer<TYPE>& other, const size_t memory_length) {
		if (memory_length == 0) {
			this->memory = nullptr;
			return;
		}
		this->memory = new TYPE[memory_length];
		copy_memory<TYPE>(other.memory, this->memory, memory_length);
		return;
		/*
		// Allocation
		this->memory = (TYPE*)(::operator new[](sizeof(TYPE)* memory_length));
		// Initialisation
		for (size_t i = 0; i < memory_length; ++i) {
			new (&this->memory[i]) TYPE(other.memory[i]);
		}*/
		return;
	}

	template <typename TYPE>
	inline void ArrayPointer<TYPE>::_cleanup_() {
		if (this->memory != nullptr) {
			delete[] this->memory;
		}
		this->memory = 0;
		return;
	}

}