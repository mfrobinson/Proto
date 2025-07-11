#pragma once
#include "Declarations/Memory Management/Pointers/Optional.h"
#include "Cast/move_cast.h"


namespace Proto {

	template <typename TYPE>
	Optional<TYPE>::Optional() : Pointer<TYPE>() {
		return;
	}

	template <typename TYPE>
	Optional<TYPE>::Optional(Pointer<TYPE>&& other) : Pointer<TYPE>(move_cast(other)) {
		return;
	}

	template <typename TYPE>
	Optional<TYPE>::Optional(const Pointer<TYPE>& other) : Pointer<TYPE>(other) {
		return;
	}

	template <typename TYPE>
	Optional<TYPE>& Optional<TYPE>::operator=(Pointer<TYPE>&& other) {
		Pointer<TYPE>::operator=(move_cast(other));
		return *this;
	}

	template <typename TYPE>
	Optional<TYPE>& Optional<TYPE>::operator=(const Pointer<TYPE>& other) {
		Pointer<TYPE>::operator=(other);
		return *this;
	}

	template <typename TYPE>
	Optional<TYPE>::~Optional() {
		return;
	}

	template <typename TYPE>
	Optional<TYPE>::Optional(TYPE instance) : Pointer<TYPE>(move_cast(instance)) {
		return;
	}

	template <typename TYPE>
	bool Optional<TYPE>::has_value() const {
		return (const TYPE*)(*this) == nullptr;
	}

}