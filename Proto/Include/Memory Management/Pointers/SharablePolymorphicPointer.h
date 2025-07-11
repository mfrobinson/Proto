#pragma once
#include "Declarations/Memory Management/Pointers/SharablePolymorphicPointer.h"
#include "Cast/move_cast.h"


namespace Proto {

	template <typename BASE>
	SharablePolymorphicPointer<BASE>::SharablePolymorphicPointer() : SharablePointer<BASE>() {
		return;
	}

	template <typename BASE>
	SharablePolymorphicPointer<BASE>::SharablePolymorphicPointer(SharablePolymorphicPointer<BASE>&& other) : SharablePointer<BASE>((SharablePointer<BASE>&&)other) {
		return;
	}

	template <typename BASE>
	SharablePolymorphicPointer<BASE>::SharablePolymorphicPointer(const SharablePolymorphicPointer<BASE>& other) : SharablePointer<BASE>((const SharablePointer<BASE>&)other) {
		return;
	}

	template <typename BASE>
	SharablePolymorphicPointer<BASE>& SharablePolymorphicPointer<BASE>::operator=(SharablePolymorphicPointer<BASE>&& other) {
		SharablePointer<BASE>::operator=((SharablePointer<BASE>&&)other);
		return *this;
	}

	template <typename BASE>
	SharablePolymorphicPointer<BASE>& SharablePolymorphicPointer<BASE>::operator=(const SharablePolymorphicPointer<BASE>& other) {
		SharablePointer<BASE>::operator=((const SharablePointer<BASE>&)other);
		return *this;
	}

	template <typename BASE>
	SharablePolymorphicPointer<BASE>::~SharablePolymorphicPointer() {
		return;
	}

	template <typename BASE>
	template <typename INSTANCE>
	SharablePolymorphicPointer<BASE>::SharablePolymorphicPointer(INSTANCE instance) : SharablePointer<BASE>() {
		this->record = new SharablePointer<BASE>::InstanceRecord{ 1, new INSTANCE(move_cast(instance)) };
		return;
	}

}