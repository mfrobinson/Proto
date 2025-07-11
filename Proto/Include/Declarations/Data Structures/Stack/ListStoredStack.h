#pragma once
#include "Data Structures/Stack/AbstractStack.h"


namespace Proto {

	/**
	* Generic stack implementation that stores its values in a list structure.
	*
	* @tparam LIST_TYPE The type of list that will be used to store the values of the stack instance.
	* @tparam TYPE The data type of all values belonging to this stack.
	*/
	template <template<typename> typename LIST_TYPE, typename TYPE>
	class ListStoredStack : public AbstractStack<TYPE> {
	public:
		/**
		* The default constructor of the stack implementation.
		*
		* This constructor initialises the instance to represent an empty stack.
		*
		* @exceptsafe The state prior to the call will be preserved if an exception is thrown.
		*/
		ListStoredStack();
		/**
		* The move constructor of the stack implementation.
		*
		* @param other The stack implementation of the same type to move content from.
		* @exceptsafe Shall not throw any exceptions.
		*/
		ListStoredStack(ListStoredStack<LIST_TYPE, TYPE>&& other) noexcept;
		/**
		* The copy constructor of the stack implementation.
		*
		* @param other The stack implementation of the same type to copy content from.
		* @exceptsafe The state prior to the call will be preserved if an exception is thrown.
		*/
		ListStoredStack(const ListStoredStack<LIST_TYPE, TYPE>& other);
		/**
		* The move operator of the stack implementation.
		*
		* @param other The stack implementation of the same type to move content from.
		* @return A reference to the instance that the content was moved to.
		* @exceptsafe Shall not throw any exceptions.
		*/
		ListStoredStack<LIST_TYPE, TYPE>& operator=(ListStoredStack<LIST_TYPE, TYPE>&& other) noexcept;
		/**
		* The copy operator of the stack implementation.
		*
		* @param other The stack implementation of the same type to copy content from.
		* @return A reference to the instance that the content was moved to.
		* @exceptsafe The state prior to the call will be preserved if an exception is thrown.
		*/
		ListStoredStack<LIST_TYPE, TYPE>& operator=(const ListStoredStack<LIST_TYPE, TYPE>& other);
		/**
		* The implementation of the stack destructor.
		*
		* @exceptsafe Shall not throw any exceptions.
		*/
		~ListStoredStack() noexcept;
		/**
		* Add a value to the top of the stack.
		*
		* @param value The value to add to the top of the stack.
		*/
		virtual void push(TYPE value) override;
		/**
		* Retrieve and remove the value on the top of the stack.
		* 
		* An exception will be thrown if there are no values in the stack to pop.
		*
		* @return The value that was removed from the top of the stack.
		*/
		virtual TYPE pop() override;
		/**
		* Retrieve a reference to the value on the top of the stack.
		* 
		* An exception will be thrown if there are no values in the stack.
		*
		* @return A reference to the value at the top of the stack.
		*/
		virtual TYPE& top() override;
		/**
		* Retrieve a reference to the value on the top of the stack,
		* but specifically in a context where the stack instance and
		* its contents are constant and not modifiable.
		* 
		* An exception will be thrown if there are no values in the stack.
		*
		* @return A constant reference to the value at the top of the stack.
		*/
		virtual const TYPE& top() const override;
		/**
		* Determine whether or not the stack implementation holds at least
		* one value.
		*
		* @return True if the stack implementation holds at least one value, otherwise false.
		* @exceptsafe Shall not throw any exceptions.
		*/
		virtual bool has_value() const noexcept override;
	protected:
		/**
		* Internal move method to streamline similarities between the move constructor and operator.
		*
		* @param other The supplied stack to move contents from. These contents will be moved into the calling instance.
		* @exceptsafe Shall not throw any exceptions.
		*/
		inline void _move_(ListStoredStack<LIST_TYPE, TYPE>& other) noexcept;
		/**
		* Internal copy method to streamline similarities between the copy constructor and operator.
		*
		* @param other The supplied stack to copy contents from. These contents will be copied into the calling instance.
		* @exceptsafe The state prior to the call will be preserved if an exception is thrown.
		*/
		inline void _copy_(const ListStoredStack<LIST_TYPE, TYPE>& other);
		/**
		* Internal cleanup method to streamline necessary deallocation in constructors, operators, and the destructor.
		*
		* @exceptsafe Shall not throw any exceptions.
		*/
		inline void _cleanup_() noexcept;
	private:
		LIST_TYPE<TYPE> internal_list;

		inline TYPE& _top_() const;
	};

}