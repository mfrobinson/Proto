#pragma once
#include "Declarations/Memory Management/Pointers/AbstractInstancePointer.h"


namespace Proto {

	template <typename TYPE>
	AbstractInstancePointer<TYPE>::~AbstractInstancePointer() {
		return;
	}

}