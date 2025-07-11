#pragma once
#include "Memory Management/Pointers/Pointer.h"


namespace Proto {

	template <typename BASE>
	class PolymorphicPointer : public Pointer<BASE> {
	public:
		PolymorphicPointer();
		PolymorphicPointer(PolymorphicPointer<BASE>&& other);
		PolymorphicPointer(const PolymorphicPointer<BASE>& other) = delete;
		PolymorphicPointer<BASE>& operator=(PolymorphicPointer<BASE>&& other);
		PolymorphicPointer<BASE>& operator=(const PolymorphicPointer<BASE>& other) = delete;
		~PolymorphicPointer();
		template <typename INSTANCE>
		PolymorphicPointer(INSTANCE instance);
	protected:
	private:
	};

}