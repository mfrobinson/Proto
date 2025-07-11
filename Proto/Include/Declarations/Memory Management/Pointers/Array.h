#pragma once
#include "Memory Management/Pointers/ArrayPointer.h"
#include <type_traits>
#include <iostream>


namespace Proto {
 
	template <typename TYPE>
	class Array : public ArrayPointer<TYPE> {
	public:
		Array();
		Array(Array<TYPE>&& other);
		Array(const Array<TYPE>& other);
		Array<TYPE>& operator=(Array<TYPE>&& other);
		Array<TYPE>& operator=(const Array<TYPE>& other);
		virtual ~Array();

		template <typename...TYPES> requires std::conjunction<std::is_same<TYPE, TYPES>...>::value
		Array(TYPES&&...values);
		template <typename...TYPES> requires std::conjunction<std::is_same<TYPE, TYPES>...>::value
		Array(const TYPES&...values);
		Array(const size_t number_of_values);
		Array(const size_t number_of_values, const TYPE& values);
		Array(const size_t number_of_values, const TYPE* values);
		virtual TYPE& operator[](const size_t index) override;
		virtual const TYPE& operator[](const size_t index) const override;
		size_t length() const;
	protected:
		inline void _move_(Array<TYPE>& other);
		inline void _copy_(const Array<TYPE>& other);
		inline void _cleanup_();
	private:
		size_t size;

		inline void _super_move_(Array<TYPE>& other);
		inline void _super_copy_(const Array<TYPE>& other);
		inline void _super_cleanup_();

		inline TYPE& access_index(const size_t index) const;
	};

	template <typename TYPE>
	std::ostream& operator<<(std::ostream& os, const Array<TYPE>& arr);

}