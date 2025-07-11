#pragma once
#include "Memory Management/Pointers/AbstractPointer.h"


namespace Proto {

	template <typename TYPE>
	class AbstractInstancePointer : public AbstractPointer<TYPE> {
	public:
		virtual ~AbstractInstancePointer() = 0;
		virtual TYPE* operator->() = 0;
		virtual const TYPE* operator->() const = 0;
	protected:
	private:
	};

}