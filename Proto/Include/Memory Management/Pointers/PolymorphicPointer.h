#pragma once
#include "Declarations/Memory Management/Pointers/PolymorphicPointer.h"
#include "Cast/move_cast.h"


namespace Proto {

	template <typename BASE>
	PolymorphicPointer<BASE>::PolymorphicPointer() : Pointer<BASE>() {
		return;
	}

	template <typename BASE>
	PolymorphicPointer<BASE>::PolymorphicPointer(PolymorphicPointer<BASE>&& other) : Pointer<BASE>((Pointer<BASE>&&)other) {
		return;
	}

	template <typename BASE>
	PolymorphicPointer<BASE>& PolymorphicPointer<BASE>::operator=(PolymorphicPointer<BASE>&& other) {
		Pointer<BASE>::operator=((Pointer<BASE>&&)other);
		return *this;
	}

	template <typename BASE>
	PolymorphicPointer<BASE>::~PolymorphicPointer() {
		return;
	}

	template <typename BASE>
	template <typename INSTANCE>
	PolymorphicPointer<BASE>::PolymorphicPointer(INSTANCE instance) : Pointer<BASE>(dynamic_cast<BASE*>((INSTANCE*)new INSTANCE(move_cast(instance)))) {
		return;
	}

}