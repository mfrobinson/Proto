#pragma once
#include "Data Structures/Dictionary/AbstractDictionary.h"
#include "Data Structures/Pair.h"


namespace Proto {

	/**
	* Generic dictionary implementation that stores its records in a list structure.
	*
	* @tparam LIST_TYPE The type of list that will be used to store the records of the dictionary instance.
	* @tparam KEY_TYPE The data type of all keys belonging to this dictionary.
	* @tparam VALUE_TYPE The data type of all values belonging to this dictionary.
	*/
	template <template<typename> typename LIST_TYPE, typename KEY_TYPE, typename VALUE_TYPE>
	class ListStoredDictionary : public AbstractDictionary<KEY_TYPE, VALUE_TYPE> {
	public:
		/**
		* The default constructor of the dictionary implementation.
		* 
		* This constructor initialises the instance to represent an empty dictionary.
		* 
		* @exceptsafe The state prior to the call will be preserved if an exception is thrown.
		*/
		ListStoredDictionary();
		/**
		* The move constructor of the dictionary implementation.
		*
		* @param other The dictionary implementation of the same type to move content from.
		* @exceptsafe Shall not throw any exceptions.
		*/
		ListStoredDictionary(ListStoredDictionary<LIST_TYPE, KEY_TYPE, VALUE_TYPE>&& other) noexcept;
		/**
		* The copy constructor of the dictionary implementation.
		*
		* @param other The dictionary implementation of the same type to copy content from.
		* @exceptsafe The state prior to the call will be preserved if an exception is thrown.
		*/
		ListStoredDictionary(const ListStoredDictionary<LIST_TYPE, KEY_TYPE, VALUE_TYPE>& other);
		/**
		* The move operator of the dictionary implementation.
		*
		* @param other The dictionary implementation of the same type to move content from.
		* @return A reference to the instance that the content was moved to.
		* @exceptsafe Shall not throw any exceptions.
		*/
		ListStoredDictionary<LIST_TYPE, KEY_TYPE, VALUE_TYPE>& operator=(ListStoredDictionary<LIST_TYPE, KEY_TYPE, VALUE_TYPE>&& other) noexcept;
		/**
		* The copy operator of the dictionary implementation.
		*
		* @param other The dictionary implementation of the same type to copy content from.
		* @return A reference to the instance that the content was moved to.
		* @exceptsafe The state prior to the call will be preserved if an exception is thrown.
		*/
		ListStoredDictionary<LIST_TYPE, KEY_TYPE, VALUE_TYPE>& operator=(const ListStoredDictionary<LIST_TYPE, KEY_TYPE, VALUE_TYPE>& other);
		/**
		* The implementation of the dictionary destructor.
		*
		* @exceptsafe Shall not throw any exceptions.
		*/
		~ListStoredDictionary() noexcept;
		/**
		* Set a key to map to a value.
		*
		* This will override a previous set operation if the keys are the equal.
		*
		* @param key The key that will be used to lookup the matching supplied value.
		* @param value The value that will be mapped from the supplied key.
		*/
		virtual void set(KEY_TYPE key, VALUE_TYPE value) override;
		/**
		* Retrieve a value by looking up a key.
		*
		* @param key The key to lookup in the dictionary.
		* @return A reference to the location of the corresponding value.
		*/
		virtual VALUE_TYPE& lookup(const KEY_TYPE& key) override;
		/**
		* Retrieve a value by looking up a key, but specifically in a
		* context where the dictionary instance and its contents are constant and
		* not modifiable.
		*
		* @param key The key to lookup in the dictionary.
		* @return A constant reference to the location of the corresponding value.
		*/
		virtual const VALUE_TYPE& lookup(const KEY_TYPE& key) const override;
		/**
		* Retrieve a key by an index into the storage solution of the instance.
		* This is usually used to iterate over all the keys that a dictionary owns.
		*
		* @param index The index to lookup in the dictionary's records for its key.
		* @return A reference to the location of the corresponding key.
		*/
		virtual KEY_TYPE& key_at(const size_t index) override;
		/**
		* Retrieve a key by an index into the storage solution of the instance, but
		* specifically in a context where the dictionary instance and its contents are
		* constant and not modifiable. This is usually used to iterate over all the
		* keys that a dictionary owns.
		*
		* @param index The index to lookup in the dictionary's records for its key.
		* @return A constant reference to the location of the corresponding key.
		*/
		virtual const KEY_TYPE& key_at(const size_t index) const override;
		/**
		* Retrieve a value by an index into the storage solution of the instance.
		* This is usually used to iterate over all the values that a dictionary owns.
		*
		* @param index The index to lookup in the dictionary's records for its value.
		* @return A reference to the location of the corresponding value.
		*/
		virtual VALUE_TYPE& value_at(const size_t index) override;
		/**
		* Retrieve a value by an index into the storage solution of the instance, but
		* specifically in a context where the dictionary instance and its contents are
		* constant and not modifiable. This is usually used to iterate over all the
		* values that a dictionary owns.
		*
		* @param index The index to lookup in the dictionary's records for its value.
		* @return A constant reference to the location of the corresponding value.
		*/
		virtual const VALUE_TYPE& value_at(const size_t index) const override;
		/**
		* Retrieve the number of records in the dictionary instance.
		*
		* @return The number of records that the instance contains.
		*/
		virtual size_t length() const noexcept override;
	protected:
		/**
		* Internal move method to streamline similarities between the move constructor and operator.
		*
		* @paramt KEY_TYPE The key type of the dictionary that data is being moved to.
		* @paramt VALUE_TYPE The value type of the dictionary that data is being moved to.
		* @param other The supplied dictionary to move contents from. These contents will be moved into the calling instance.
		* @exceptsafe Shall not throw any exceptions.
		*/
		inline void _move_(ListStoredDictionary<LIST_TYPE, KEY_TYPE, VALUE_TYPE>& other) noexcept;
		/**
		* Internal copy method to streamline similarities between the copy constructor and operator.
		*
		* @paramt KEY_TYPE The key type of the dictionary that data is being copied to.
		* @paramt VALUE_TYPE The value type of the dictionary that data is being copied to.
		* @param other The supplied dictionary to copy contents from. These contents will be copied into the calling instance.
		* @exceptsafe The state prior to the call will be preserved if an exception is thrown.
		*/
		inline void _copy_(const ListStoredDictionary<LIST_TYPE, KEY_TYPE, VALUE_TYPE>& other);
		/**
		* Internal cleanup method to streamline necessary deallocation in constructors, operators, and the destructor.
		*
		* @exceptsafe Shall not throw any exceptions.
		*/
		inline void _cleanup_() noexcept;
	private:
		LIST_TYPE<Pair<KEY_TYPE, VALUE_TYPE>> internal_list;

		const VALUE_TYPE& _lookup_(const KEY_TYPE& key) const;
		const KEY_TYPE& _key_at_(const size_t index) const;
		const VALUE_TYPE& _value_at_(const size_t index) const;
	};

}