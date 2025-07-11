#pragma once
#include <iostream>


namespace Proto {

	/**
	* Abstract class that acts as an interface for dictionaries.
	* 
	* This class provides all the necessary abstract functions that
	* a well-defined dictionary must implement. It is a good idea to
	* use this as a reference parameter type when passing a dictionary,
	* provided that the specific implementation does not matter.
	* 
	* @tparam KEY_TYPE The data type of all keys belonging to this dictionary.
	* @tparam VALUE_TYPE The data type of all values belonging to this dictionary.
	*/
	template <typename KEY_TYPE, typename VALUE_TYPE>
	class AbstractDictionary {
	public:
		/**
		* The virtual destructor of the interface.
		* 
		* This insures that any deallocation of a Dictionary instance being treated
		* as an AbstractDictionary will have the appropriate derived destructor called.
		* 
		* @exceptsafe Shall not throw any exceptions.
		*/
		virtual ~AbstractDictionary() noexcept;
		/**
		* Set a key to map to a value.
		* 
		* @param key The key that will be used to lookup the matching supplied value.
		* @param value The value that will be mapped from the supplied key.
		*/
		virtual void set(KEY_TYPE key, VALUE_TYPE value) = 0;
		/**
		* Retrieve a value by looking up a key.
		* 
		* @param key The key to lookup in the dictionary.
		* @return A reference to the location of the corresponding value.
		*/
		virtual VALUE_TYPE& lookup(const KEY_TYPE& key) = 0;
		/**
		* Retrieve a value by looking up a key, but specifically in a
		* context where the dictionary instance and its contents are constant and
		* not modifiable.
		*
		* @param key The key to lookup in the dictionary.
		* @return A constant reference to the location of the corresponding value.
		*/
		virtual const VALUE_TYPE& lookup(const KEY_TYPE& key) const = 0;
		/**
		* Retrieve a key by an index into the storage solution of the instance.
		* This is usually used to iterate over all the keys that a dictionary owns.
		*
		* @param index The index to lookup in the dictionary's records for its key.
		* @return A reference to the location of the corresponding key.
		*/
		virtual KEY_TYPE& key_at(const size_t index) = 0;
		/**
		* Retrieve a key by an index into the storage solution of the instance, but
		* specifically in a context where the dictionary instance and its contents are
		* constant and not modifiable. This is usually used to iterate over all the
		* keys that a dictionary owns.
		*
		* @param index The index to lookup in the dictionary's records for its key.
		* @return A constant reference to the location of the corresponding key.
		*/
		virtual const KEY_TYPE& key_at(const size_t index) const = 0;
		/**
		* Retrieve a value by an index into the storage solution of the instance.
		* This is usually used to iterate over all the values that a dictionary owns.
		*
		* @param index The index to lookup in the dictionary's records for its value.
		* @return A reference to the location of the corresponding value.
		*/
		virtual VALUE_TYPE& value_at(const size_t index) = 0;
		/**
		* Retrieve a value by an index into the storage solution of the instance, but
		* specifically in a context where the dictionary instance and its contents are
		* constant and not modifiable. This is usually used to iterate over all the
		* values that a dictionary owns.
		*
		* @param index The index to lookup in the dictionary's records for its value.
		* @return A constant reference to the location of the corresponding value.
		*/
		virtual const VALUE_TYPE& value_at(const size_t index) const = 0;
		/**
		* Retrieve the number of records in the dictionary instance.
		* 
		* @return The number of records that the instance contains.
		*/
		virtual size_t length() const noexcept = 0;
	protected:
	private:
	};

	/**
	* Generalised output operator that defines an output operator for every well-defined dictionary.
	* 
	* @tparam KEY_TYPE The data type of the keys belonging to the dictionary.
	* @tparam VALUE_TYPE The data type of the values belonging to the dictionary.
	* @param os A reference to the standard output stream which should be written to.
	* @param dictionary A constant reference to the dictionary which should be used to generate the output to the stream.
	* @return The same standard output reference that was supplied in the os parameter.
	*/
	template <typename KEY_TYPE, typename VALUE_TYPE>
	std::ostream& operator<<(std::ostream& os, const AbstractDictionary<KEY_TYPE, VALUE_TYPE>& dictionary);

}