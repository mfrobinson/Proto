#pragma once
#include "Declarations/Cast/move_cast.h"


namespace Proto {

	template <typename TYPE>
	TYPE&& move_cast(TYPE& value) noexcept {
		return (TYPE&&)value;
	}

}