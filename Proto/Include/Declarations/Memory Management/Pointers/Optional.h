#pragma once
#include "Memory Management/Pointers/Pointer.h"


namespace Proto {

	template <typename TYPE>
	class Optional : public Pointer<TYPE> {
	public:
		Optional();
		Optional(Pointer<TYPE>&& other);
		Optional(const Pointer<TYPE>& other);
		Optional<TYPE>& operator=(Pointer<TYPE>&& other);
		Optional<TYPE>& operator=(const Pointer<TYPE>& other);
		~Optional();

		Optional(TYPE instance);

		bool has_value() const;
	protected:
	private:
	};

}