#pragma once
#include <iostream>


namespace Proto {

	/**
	* Abstract class that acts as an interface for list.
	*
	* This class provides all the necessary abstract functions that
	* a well-defined list must implement. It is a good idea to
	* use this as a reference parameter type when passing a list,
	* provided that the specific implementation does not matter.
	*
	* @tparam TYPE The data type of all values belonging to this list.
	*/
	template <typename TYPE>
	class AbstractList {
	public:
		/**
		* The virtual destructor of the interface.
		*
		* This insures that any deallocation of a List instance being treated
		* as an AbstractList will have the appropriate derived destructor called.
		*
		* @exceptsafe Shall not throw any exceptions.
		*/
		virtual ~AbstractList() noexcept;
		/**
		* Add a value to the end of the list.
		*
		* @param value The value that will be added to the list.
		*/
		virtual void append(TYPE value) = 0;
		/**
		* Retrieve a value by an index into the list.
		*
		* @param index The index to lookup in the list's values.
		* @return A reference to the location of the corresponding index.
		*/
		virtual TYPE& get(const size_t index) = 0;
		/**
		* Retrieve a value by an index into the list, but specifically in a context
		* where the list instance and its contents are constant and not modifiable.
		*
		* @param index The index to lookup in the list's values.
		* @return A constant reference to the location of the corresponding index.
		*/
		virtual const TYPE& get(const size_t index) const = 0;
		/**
		* Remove and return a value from the list by index.
		* 
		* @param index The index of the value to remove and return from the list.
		* @return The value that was removed from the list.
		*/
		virtual TYPE pop(const size_t index) = 0;
		/**
		* Retrieve the number of values in the list instance.
		*
		* @return The number of values that the instance contains.
		* @exceptsafe Shall not throw any exceptions.
		*/
		virtual size_t length() const noexcept = 0;
	protected:
	private:
	};

	/**
	* Generalised output operator that defines an output operator for every well-defined list.
	*
	* @tparam TYPE The data type of the values belonging to the list.
	* @param os A reference to the standard output stream which should be written to.
	* @param list A constant reference to the list which should be used to generate the output to the stream.
	* @return The same standard output reference that was supplied in the os parameter.
	*/
	template <typename TYPE>
	std::ostream& operator<<(std::ostream& os, const AbstractList<TYPE>& list);

}