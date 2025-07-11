#pragma once
#include "Cast/move_cast.h"


namespace Proto {

	template <typename TYPE>
	void move_memory(TYPE* from, TYPE* to, const size_t count);

}