#pragma once
#include "Memory Management/Pointers/AbstractInstancePointer.h"


namespace Proto {

	template <typename TYPE>
	class AbstractArrayPointer : public AbstractPointer<TYPE> {
	public:
		virtual ~AbstractArrayPointer() = 0;
		virtual TYPE& operator[](const size_t index) = 0;
		virtual const TYPE& operator[](const size_t index) const = 0;
	protected:
	private:
	};

}