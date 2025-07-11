#pragma once
#include "Memory Management/Pointers/SharablePointer.h"


namespace Proto {

	template <typename BASE>
	class SharablePolymorphicPointer : public SharablePointer<BASE> {
	public:
		SharablePolymorphicPointer();
		SharablePolymorphicPointer(SharablePolymorphicPointer<BASE>&& other);
		SharablePolymorphicPointer(const SharablePolymorphicPointer<BASE>& other);
		SharablePolymorphicPointer<BASE>& operator=(SharablePolymorphicPointer<BASE>&& other);
		SharablePolymorphicPointer<BASE>& operator=(const SharablePolymorphicPointer<BASE>& other);
		~SharablePolymorphicPointer();
		template <typename INSTANCE>
		SharablePolymorphicPointer(INSTANCE instance);
	protected:
	private:
	};

}