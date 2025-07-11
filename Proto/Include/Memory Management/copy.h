#pragma once


namespace Proto {

	template <typename TYPE>
	TYPE copy(const TYPE& source) {
		return TYPE(source);
	}

}