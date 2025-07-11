#pragma once


namespace Proto {

	template <typename TYPE>
	TYPE& ref_cast(const TYPE& target) {
		return (TYPE&)target;
	}

}