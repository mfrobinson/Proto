#pragma once
#include "Declarations/Memory Management/Pointers/Pointer.h"
#include "Cast/move_cast.h"
#include <type_traits>


namespace Proto {

	template <typename TYPE>
	Pointer<TYPE>::Pointer() : instance(nullptr) {
		return;
	}

	template <typename TYPE>
	Pointer<TYPE>::Pointer(Pointer<TYPE>&& other) {
		this->_move_(other);
		return;
	}

	template <typename TYPE>
	Pointer<TYPE>::Pointer(const Pointer<TYPE>& other) {
		this->_copy_(other);
		return;
	}

	template <typename TYPE>
	Pointer<TYPE>& Pointer<TYPE>::operator=(Pointer<TYPE>&& other) {
		if (&other != this) {
			this->_cleanup_();
			this->_move_(other);
		}
		return *this;
	}

	template <typename TYPE>
	Pointer<TYPE>& Pointer<TYPE>::operator=(const Pointer<TYPE>& other) {
		if (&other != this) {
			this->_cleanup_();
			this->_copy_(other);
		}
		return *this;
	}

	template <typename TYPE>
	Pointer<TYPE>::~Pointer() {
		this->_cleanup_();
		return;
	}

	template <typename TYPE>
	Pointer<TYPE>::Pointer(TYPE instance) : instance(new TYPE(move_cast(instance))) {
		return;
	}

	template <typename TYPE>
	Pointer<TYPE>::operator TYPE* () {
		return this->instance;
	}

	template <typename TYPE>
	Pointer<TYPE>::operator const TYPE* () const {
		return this->instance;
	}

	template <typename TYPE>
	TYPE* Pointer<TYPE>::operator->() {
		return this->instance;
	}

	template <typename TYPE>
	const TYPE* Pointer<TYPE>::operator->() const {
		return this->instance;
	}

	template <typename TYPE>
	Pointer<TYPE>::Pointer(TYPE* instance) : instance(instance) {
		return;
	}

	template <typename TYPE>
	inline void Pointer<TYPE>::_move_(Pointer<TYPE>& other) {
		this->instance = other.instance;
		other.instance = nullptr;
		return;
	}

	template <typename TYPE>
	inline void Pointer<TYPE>::_copy_(const Pointer<TYPE>& other) requires std::derived_from<TYPE, Cloneable<TYPE>> {
		if (other.instance == nullptr) {
			this->instance = nullptr;
		}
		else {
			Pointer<TYPE> cloned = other->clone();
			this->_move_(cloned);
		}
		return;
	}

	template <typename TYPE>
	inline void Pointer<TYPE>::_copy_(const Pointer<TYPE>& other) requires (!std::derived_from<TYPE, Cloneable<TYPE>>) {
		if (other.instance == nullptr) {
			this->instance = nullptr;
		}
		else {
			this->instance = new TYPE(*other.instance);
		}
		return;
	}

	template <typename TYPE>
	inline void Pointer<TYPE>::_cleanup_() {
		if (this->instance != nullptr) {
			delete this->instance;
		}
		return;
	}

}