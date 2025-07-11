#pragma once
#include "Declarations/Data Structures/Stack/ListStoredStack.h"
#include "Cast/move_cast.h"


namespace Proto {

	template <template<typename> typename LIST_TYPE, typename TYPE>
	ListStoredStack<LIST_TYPE, TYPE>::ListStoredStack() {
		return;
	}

	template <template<typename> typename LIST_TYPE, typename TYPE>
	ListStoredStack<LIST_TYPE, TYPE>::ListStoredStack(ListStoredStack<LIST_TYPE, TYPE>&& other) noexcept {
		this->_move_(other);
		return;
	}

	template <template<typename> typename LIST_TYPE, typename TYPE>
	ListStoredStack<LIST_TYPE, TYPE>::ListStoredStack(const ListStoredStack<LIST_TYPE, TYPE>& other) {
		this->_copy_(other);
		return;
	}

	template <template<typename> typename LIST_TYPE, typename TYPE>
	ListStoredStack<LIST_TYPE, TYPE>& ListStoredStack<LIST_TYPE, TYPE>::operator=(ListStoredStack<LIST_TYPE, TYPE>&& other) noexcept {
		if (&other != this) {
			this->_cleanup_(other);
			this->_move_(other);
		}
		return *this;
	}

	template <template<typename> typename LIST_TYPE, typename TYPE>
	ListStoredStack<LIST_TYPE, TYPE>& ListStoredStack<LIST_TYPE, TYPE>::operator=(const ListStoredStack<LIST_TYPE, TYPE>& other) {
		if (&other != this) {
			this->_cleanup_(other);
			this->_copy_(other);
		}
		return *this;
	}

	template <template<typename> typename LIST_TYPE, typename TYPE>
	ListStoredStack<LIST_TYPE, TYPE>::~ListStoredStack() noexcept {
		this->_cleanup_();
	}

	template <template<typename> typename LIST_TYPE, typename TYPE>
	void ListStoredStack<LIST_TYPE, TYPE>::push(TYPE value) {
		this->internal_list.append(move_cast(value));
		return;
	}

	template <template<typename> typename LIST_TYPE, typename TYPE>
	TYPE ListStoredStack<LIST_TYPE, TYPE>::pop() {
		return this->internal_list.pop(this->internal_list.length() - 1);
	}

	template <template<typename> typename LIST_TYPE, typename TYPE>
	TYPE& ListStoredStack<LIST_TYPE, TYPE>::top() {
		return this->_top_();
	}

	template <template<typename> typename LIST_TYPE, typename TYPE>
	const TYPE& ListStoredStack<LIST_TYPE, TYPE>::top() const {
		return this->_top_();
	}

	template <template<typename> typename LIST_TYPE, typename TYPE>
	bool ListStoredStack<LIST_TYPE, TYPE>::has_value() const noexcept {
		return this->internal_list.length() > 0;
	}

	template <template<typename> typename LIST_TYPE, typename TYPE>
	inline void ListStoredStack<LIST_TYPE, TYPE>::_move_(ListStoredStack<LIST_TYPE, TYPE>& other) noexcept {
		this->internal_list = move_cast(other.internal_list);
		return;
	}

	template <template<typename> typename LIST_TYPE, typename TYPE>
	inline void ListStoredStack<LIST_TYPE, TYPE>::_copy_(const ListStoredStack<LIST_TYPE, TYPE>& other) {
		this->internal_list = other.internal_list;
		return;
	}

	template <template<typename> typename LIST_TYPE, typename TYPE>
	inline void ListStoredStack<LIST_TYPE, TYPE>::_cleanup_() noexcept {
		return;
	}

	template <template<typename> typename LIST_TYPE, typename TYPE>
	inline TYPE& ListStoredStack<LIST_TYPE, TYPE>::_top_() const {
		return (TYPE&)this->internal_list.get(this->internal_list.length() - 1);
	}

}