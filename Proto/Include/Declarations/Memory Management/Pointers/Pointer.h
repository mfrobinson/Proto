#pragma once
#include "Memory Management/Pointers/AbstractInstancePointer.h"
#include "Memory Management/Cloneable.h"
#include <concepts>


namespace Proto {

	template <typename TYPE>
	class Pointer : public AbstractInstancePointer<TYPE> {
	public:
		Pointer();
		Pointer(Pointer<TYPE>&& other);
		Pointer(const Pointer<TYPE>& other);
		Pointer<TYPE>& operator=(Pointer<TYPE>&& other);
		Pointer<TYPE>& operator=(const Pointer<TYPE>& other);
		virtual ~Pointer();
		Pointer(TYPE instance);
		virtual operator TYPE* () override;
		virtual operator const TYPE* () const override;
		virtual TYPE* operator->() override;
		virtual const TYPE* operator->() const override;
	protected:
		TYPE* instance;

		Pointer(TYPE* instance);

		inline void _move_(Pointer<TYPE>& other);
		inline void _copy_(const Pointer<TYPE>& other) requires std::derived_from<TYPE, Cloneable<TYPE>>;
		inline void _copy_(const Pointer<TYPE>& other) requires (!std::derived_from<TYPE, Cloneable<TYPE>>);
		inline void _cleanup_();
	private:
	};

}