#pragma once


namespace Proto {

	/**
	* Casts the type of the supplied value into an explicit move type.
	* 
	* This forces the invocation of the move constructor/operator
	* as opposed to the copy constructor/operator.
	* 
	* @tparam TYPE The data type of the value being passed.
	* @param[in] value The instance that should result in being moved.
	* @return The instance supplied cast to an explicitly movable type.
	* @exceptsafe Shall not throw any exceptions.
	*/
	template <typename TYPE>
	TYPE&& move_cast(TYPE& value) noexcept;

}