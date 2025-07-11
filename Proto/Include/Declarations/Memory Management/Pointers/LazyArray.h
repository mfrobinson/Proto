#pragma once
#include "Memory Management/Pointers/ArrayPointer.h"
#include "Memory Management/Pointers/Optional.h"


namespace Proto {

	/**
	* The LazyArray class delays initialisation of instances until they are assigned.
	* This potentially reduces runtime costs as the entire allocated memory may not need to be initialised.
	* However, utilisation of this class can increase memory usage due to the fact that each instace is stored separately
	* (heap bookkeeping is repeated for each instance).
	*/
	template <typename TYPE>
	class LazyArray : ArrayPointer<Optional<TYPE>> {
	public:
		LazyArray();
		LazyArray(LazyArray<TYPE>&& other);
		LazyArray(const LazyArray<TYPE>& other);
		LazyArray<TYPE>& operator=(LazyArray<TYPE>&& other);
		LazyArray<TYPE>& operator=(const LazyArray<TYPE>& other);
		~LazyArray();

		// Allocate memory and initialise by moving the instances provided
		template <typename...TYPES>
		LazyArray(TYPES&&...values);
		// Allocate memory and initialise by copying the instances provided
		template <typename...TYPES>
		LazyArray(const TYPES&...values);
		// Allocate memory, but no initialisation
		LazyArray(const size_t number_of_values);
		// Allocate memory and initialise to a copy of an instance
		LazyArray(const size_t number_of_values, const TYPE& value);
		// Allocate memory and initialise to a copy of a set of instances
		LazyArray(const size_t number_of_values, const TYPE* values);

		size_t length() const;

		/*
		void initialise(const size_t index, TYPE&& value);
		void initialise(const size_t index, const TYPE& value);

		virtual operator TYPE* () override;
		virtual operator const TYPE* () const override;
		virtual TYPE& operator[](const size_t index) override;
		virtual const TYPE& operator[](const size_t index) const override;
		*/

		virtual Optional<TYPE>& operator[](const size_t index) override;
		virtual const Optional<TYPE>& operator[](const size_t index) const override;
	protected:
		inline void _move_(LazyArray<TYPE>& other);
		inline void _copy_(const LazyArray<TYPE>& other);
		inline void _cleanup_();
		inline void _super_move_(LazyArray<TYPE>& other);
		inline void _super_copy_(const LazyArray<TYPE>& other);
		inline void _super_cleanup_();
	private:
		size_t size;

		inline Optional<TYPE>& access_index(const size_t index) const;
	};

}