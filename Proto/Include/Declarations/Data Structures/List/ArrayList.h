#pragma once
#include "Data Structures/List/AbstractList.h"
#include "Memory Management/Pointers/Array.h"


namespace Proto {
	
	/**
	* List implementation that utilises an array structure to store
	* values.
	*
	* This implementation provides access speed at the cost of potential
	* memory overhead and occasionally longer append run-times to upsize
	* the internal array.
	*
	* @tparam TYPE The data type of all values belonging to this list.
	*/
	template <typename TYPE>
	class ArrayList : public AbstractList<TYPE> {
	public:
		/**
		* The default constructor of the list implementation.
		*
		* This constructor initialises the instance to represent an empty list.
		* 
		* @exceptsafe The state prior to the call will be preserved if an exception is thrown.
		*/
		ArrayList();
		/**
		* The move constructor of the list implementation.
		*
		* @param other The list implementation of the same type to move content from.
		* @exceptsafe Shall not throw any exceptions.
		*/
		ArrayList(ArrayList<TYPE>&& other) noexcept;
		/**
		* The copy constructor of the list implementation.
		*
		* @param other The list implementation of the same type to copy content from.
		* @exceptsafe The state prior to the call will be preserved if an exception is thrown.
		*/
		ArrayList(const ArrayList<TYPE>& other);
		/**
		* The move operator of the list implementation.
		*
		* @param other The list implementation of the same type to move content from.
		* @return A reference to the instance that the content was moved to.
		* @exceptsafe Shall not throw any exceptions.
		*/
		ArrayList<TYPE>& operator=(ArrayList<TYPE>&& other) noexcept;
		/**
		* The copy operator of the list implementation.
		*
		* @param other The list implementation of the same type to copy content from.
		* @return A reference to the instance that the content was moved to.
		* @exceptsafe The state prior to the call will be preserved if an exception is thrown.
		*/
		ArrayList<TYPE>& operator=(const ArrayList<TYPE>& other);
		/**
		* The implementation of the list destructor.
		*
		* @exceptsafe Shall not throw any exceptions.
		*/
		~ArrayList() noexcept;
		/**
		* Add a value to the end of the list.
		*
		* @param value The value that will be added to the list.
		*/
		virtual void append(TYPE value) override;
		/**
		* Retrieve a value by an index into the list.
		*
		* @param index The index to lookup in the list's values.
		* @return A reference to the location of the corresponding index.
		*/
		virtual TYPE& get(const size_t index) override;
		/**
		* Retrieve a value by an index into the list, but specifically in a context
		* where the list instance and its contents are constant and not modifiable.
		*
		* @param index The index to lookup in the list's values.
		* @return A constant reference to the location of the corresponding index.
		*/
		virtual const TYPE& get(const size_t index) const override;
		/**
		* Remove and return a value from the list by index.
		*
		* @param index The index of the value to remove and return from the list.
		* @return The value that was removed from the list.
		*/
		virtual TYPE pop(const size_t index) override;
		/**
		* Retrieve the number of values in the list instance.
		*
		* @return The number of values that the instance contains.
		* @exceptsafe Shall not throw any exceptions.
		*/
		virtual size_t length() const noexcept override;
	protected:
		/**
		* Internal move method to streamline similarities between the move constructor and operator.
		*
		* @param other The supplied list to move contents from. These contents will be moved into the calling instance.
		* @exceptsafe Shall not throw any exceptions.
		*/
		inline void _move_(ArrayList<TYPE>& other) noexcept;
		/**
		* Internal copy method to streamline similarities between the copy constructor and operator.
		*
		* @param other The supplied list to copy contents from. These contents will be copied into the calling instance.
		* @exceptsafe The state prior to the call will be preserved if an exception is thrown.
		*/
		inline void _copy_(const ArrayList<TYPE>& other);
		/**
		* Internal cleanup method to streamline necessary deallocation in constructors, operators, and the destructor.
		*
		* @exceptsafe Shall not throw any exceptions.
		*/
		inline void _cleanup_() noexcept;
	private:
		size_t space_used;
		Array<TYPE> internal_array;

		inline void upsize_internal_array();
	};

}