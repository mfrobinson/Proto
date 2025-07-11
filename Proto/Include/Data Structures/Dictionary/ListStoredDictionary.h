#pragma once
#include "Declarations/Data Structures/Dictionary/ListStoredDictionary.h"
#include "Cast/move_cast.h"


namespace Proto {

	template <template<typename> typename LIST_TYPE, typename KEY_TYPE, typename VALUE_TYPE>
	ListStoredDictionary<LIST_TYPE, KEY_TYPE, VALUE_TYPE>::ListStoredDictionary() {
		return;
	}

	template <template<typename> typename LIST_TYPE, typename KEY_TYPE, typename VALUE_TYPE>
	ListStoredDictionary<LIST_TYPE, KEY_TYPE, VALUE_TYPE>::ListStoredDictionary(ListStoredDictionary<LIST_TYPE, KEY_TYPE, VALUE_TYPE>&& other) noexcept {
		this->_move_(other);
		return;
	}

	template <template<typename> typename LIST_TYPE, typename KEY_TYPE, typename VALUE_TYPE>
	ListStoredDictionary<LIST_TYPE, KEY_TYPE, VALUE_TYPE>::ListStoredDictionary(const ListStoredDictionary<LIST_TYPE, KEY_TYPE, VALUE_TYPE>& other) {
		this->_copy_(other);
		return;
	}

	template <template<typename> typename LIST_TYPE, typename KEY_TYPE, typename VALUE_TYPE>
	ListStoredDictionary<LIST_TYPE, KEY_TYPE, VALUE_TYPE>& ListStoredDictionary<LIST_TYPE, KEY_TYPE, VALUE_TYPE>::operator=(ListStoredDictionary<LIST_TYPE, KEY_TYPE, VALUE_TYPE>&& other) noexcept {
		if (&other != this) {
			this->_cleanup_();
			this->_move_(other);
		}
		return *this;
	}

	template <template<typename> typename LIST_TYPE, typename KEY_TYPE, typename VALUE_TYPE>
	ListStoredDictionary<LIST_TYPE, KEY_TYPE, VALUE_TYPE>& ListStoredDictionary<LIST_TYPE, KEY_TYPE, VALUE_TYPE>::operator=(const ListStoredDictionary<LIST_TYPE, KEY_TYPE, VALUE_TYPE>& other) {
		if (&other != this) {
			this->_cleanup_();
			this->_copy_(other);
		}
		return *this;
	}

	template <template<typename> typename LIST_TYPE, typename KEY_TYPE, typename VALUE_TYPE>
	ListStoredDictionary<LIST_TYPE, KEY_TYPE, VALUE_TYPE>::~ListStoredDictionary() noexcept {
		this->_cleanup_();
		return;
	}

	template <template<typename> typename LIST_TYPE, typename KEY_TYPE, typename VALUE_TYPE>
	void ListStoredDictionary<LIST_TYPE, KEY_TYPE, VALUE_TYPE>::set(KEY_TYPE key, VALUE_TYPE value) {
		Pair<KEY_TYPE, VALUE_TYPE>* current;
		for (size_t i = 0; i < this->internal_list.length(); ++i) {
			current = &this->internal_list.get(i);
			if (current->key == key) {
				current->value = move_cast(value);
				return;
			}
		}
		Pair<KEY_TYPE, VALUE_TYPE> pair{ move_cast(key), move_cast(value) };
		this->internal_list.append(move_cast(pair));
		return;
	}

	template <template<typename> typename LIST_TYPE, typename KEY_TYPE, typename VALUE_TYPE>
	VALUE_TYPE& ListStoredDictionary<LIST_TYPE, KEY_TYPE, VALUE_TYPE>::lookup(const KEY_TYPE& key) {
		return (VALUE_TYPE&)(this->_lookup_(key));
	}

	template <template<typename> typename LIST_TYPE, typename KEY_TYPE, typename VALUE_TYPE>
	const VALUE_TYPE& ListStoredDictionary<LIST_TYPE, KEY_TYPE, VALUE_TYPE>::lookup(const KEY_TYPE& key) const {
		return this->_lookup_(key);
	}

	template <template<typename> typename LIST_TYPE, typename KEY_TYPE, typename VALUE_TYPE>
	KEY_TYPE& ListStoredDictionary<LIST_TYPE, KEY_TYPE, VALUE_TYPE>::key_at(const size_t index) {
		return (KEY_TYPE&)(this->_key_at_(index));
	}

	template <template<typename> typename LIST_TYPE, typename KEY_TYPE, typename VALUE_TYPE>
	const KEY_TYPE& ListStoredDictionary<LIST_TYPE, KEY_TYPE, VALUE_TYPE>::key_at(const size_t index) const {
		return this->_key_at_(index);
	}

	template <template<typename> typename LIST_TYPE, typename KEY_TYPE, typename VALUE_TYPE>
	VALUE_TYPE& ListStoredDictionary<LIST_TYPE, KEY_TYPE, VALUE_TYPE>::value_at(const size_t index) {
		return (VALUE_TYPE&)(this->_value_at_(index));
	}

	template <template<typename> typename LIST_TYPE, typename KEY_TYPE, typename VALUE_TYPE>
	const VALUE_TYPE& ListStoredDictionary<LIST_TYPE, KEY_TYPE, VALUE_TYPE>::value_at(const size_t index) const {
		return this->_value_at_(index);
	}

	template <template<typename> typename LIST_TYPE, typename KEY_TYPE, typename VALUE_TYPE>
	size_t ListStoredDictionary<LIST_TYPE, KEY_TYPE, VALUE_TYPE>::length() const noexcept {
		return this->internal_list.length();
	}

	template <template<typename> typename LIST_TYPE, typename KEY_TYPE, typename VALUE_TYPE>
	inline void ListStoredDictionary<LIST_TYPE, KEY_TYPE, VALUE_TYPE>::_move_(ListStoredDictionary<LIST_TYPE, KEY_TYPE, VALUE_TYPE>& other) noexcept {
		this->internal_list = move_cast(other.internal_list);
		return;
	}

	template <template<typename> typename LIST_TYPE, typename KEY_TYPE, typename VALUE_TYPE>
	inline void ListStoredDictionary<LIST_TYPE, KEY_TYPE, VALUE_TYPE>::_copy_(const ListStoredDictionary<LIST_TYPE, KEY_TYPE, VALUE_TYPE>& other) {
		this->internal_list = other.internal_list;
		return;
	}

	template <template<typename> typename LIST_TYPE, typename KEY_TYPE, typename VALUE_TYPE>
	inline void ListStoredDictionary<LIST_TYPE, KEY_TYPE, VALUE_TYPE>::_cleanup_() noexcept {
		return;
	}

	template <template<typename> typename LIST_TYPE, typename KEY_TYPE, typename VALUE_TYPE>
	const VALUE_TYPE& ListStoredDictionary<LIST_TYPE, KEY_TYPE, VALUE_TYPE>::_lookup_(const KEY_TYPE& key) const {
		const Pair<KEY_TYPE, VALUE_TYPE>* current;
		for (size_t i = 0; i < this->internal_list.length(); ++i) {
			current = &this->internal_list.get(i);
			if (current->key == key) {
				return current->value;
			}
		}
		throw std::runtime_error("Dictionary does not contain specified value!");
	}

	template <template<typename> typename LIST_TYPE, typename KEY_TYPE, typename VALUE_TYPE>
	const KEY_TYPE& ListStoredDictionary<LIST_TYPE, KEY_TYPE, VALUE_TYPE>::_key_at_(const size_t index) const {
		return this->internal_list.get(index).key;
	}

	template <template<typename> typename LIST_TYPE, typename KEY_TYPE, typename VALUE_TYPE>
	const VALUE_TYPE& ListStoredDictionary<LIST_TYPE, KEY_TYPE, VALUE_TYPE>::_value_at_(const size_t index) const {
		return this->internal_list.get(index).value;
	}

}