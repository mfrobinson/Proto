#pragma once
#include "Memory Management/Pointers/AbstractArrayPointer.h"
#include <type_traits>


namespace Proto {

	template <typename TYPE>
	class ArrayPointer : public AbstractArrayPointer<TYPE> {
	public:
		ArrayPointer();
		ArrayPointer(ArrayPointer<TYPE>&& other);
		ArrayPointer(const ArrayPointer<TYPE>& other) = delete;
		ArrayPointer<TYPE>& operator=(ArrayPointer<TYPE>&& other);
		ArrayPointer<TYPE>& operator=(const ArrayPointer<TYPE>& other) = delete;
		virtual ~ArrayPointer();

		// Allocate memory and initialise by moving the instances provided
		template <typename...TYPES>
		ArrayPointer(TYPES&&...values);
		// Allocate memory and initialise by copying the instances provided
		template <typename...TYPES>
		ArrayPointer(const TYPES&...values);
		// Allocate memory, but no initialisation
		ArrayPointer(const size_t number_of_values);
		// Allocate memory and initialise to a copy of an instance
		ArrayPointer(const size_t number_of_values, const TYPE& value);
		// Allocate memory and initialise to a copy of a set of instances
		ArrayPointer(const size_t number_of_values, const TYPE* values);

		virtual operator TYPE* () override;
		virtual operator const TYPE* () const override;
		virtual TYPE& operator[](const size_t index) override;
		virtual const TYPE& operator[](const size_t index) const override;
	protected:
		TYPE* memory;

		inline void _move_(ArrayPointer<TYPE>& other);
		inline void _copy_(const ArrayPointer<TYPE>& other, const size_t memory_length);
		inline void _cleanup_();
	private:
	};

}