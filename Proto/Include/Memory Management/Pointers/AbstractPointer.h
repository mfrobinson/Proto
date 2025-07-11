#pragma once
#include "Declarations/Memory Management/Pointers/AbstractPointer.h"


namespace Proto {

	template <typename TYPE>
	AbstractPointer<TYPE>::~AbstractPointer() {
		return;
	}

}