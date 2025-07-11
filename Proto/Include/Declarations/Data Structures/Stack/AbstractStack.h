#pragma once


namespace Proto {

	/**
	* Abstract class that acts as an interface for stacks.
	*
	* This class provides all the necessary abstract functions that
	* a well-defined stack must implement. It is a good idea to
	* use this as a reference parameter type when passing a stack,
	* provided that the specific implementation does not matter.
	*
	* @tparam TYPE The data type of all values belonging to this stack.
	*/
	template <typename TYPE>
	class AbstractStack {
	public:
		/**
		* The virtual destructor of the interface.
		*
		* This insures that any deallocation of a Stack instance being treated
		* as an AbstractStack will have the appropriate derived destructor called.
		*
		* @exceptsafe Shall not throw any exceptions.
		*/
		virtual ~AbstractStack() noexcept;
		/**
		* Add a value to the top of the stack.
		*
		* @param value The value to add to the top of the stack.
		*/
		virtual void push(TYPE value) = 0;
		/**
		* Retrieve and remove the value on the top of the stack.
		*
		* @return The value that was removed from the top of the stack.
		*/
		virtual TYPE pop() = 0;
		/**
		* Retrieve a reference to the value on the top of the stack.
		*
		* @return A reference to the value at the top of the stack.
		*/
		virtual TYPE& top() = 0;
		/**
		* Retrieve a reference to the value on the top of the stack, 
		* but specifically in a context where the stack instance and
		* its contents are constant and not modifiable.
		*
		* @return A constant reference to the value at the top of the stack.
		*/
		virtual const TYPE& top() const = 0;
		/**
		* Determine whether or not the stack implementation holds at least
		* one value.
		*
		* @return True if the stack implementation holds at least one value, otherwise false.
		* @exceptsafe Shall not throw any exceptions.
		*/
		virtual bool has_value() const noexcept = 0;
	protected:
	private:
	};

}