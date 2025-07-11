#pragma once
#include "Declarations/Memory Management/Pointers/SharablePointer.h"
#include "Cast/move_cast.h"


namespace Proto {

	template <typename TYPE>
	SharablePointer<TYPE>::SharablePointer() : record(nullptr) {
		return;
	}

	template <typename TYPE>
	SharablePointer<TYPE>::SharablePointer(SharablePointer<TYPE>&& other) {
		this->_move_(other);
		return;
	}

	template <typename TYPE>
	SharablePointer<TYPE>::SharablePointer(const SharablePointer<TYPE>& other) {
		this->_copy_(other);
		return;
	}

	template <typename TYPE>
	SharablePointer<TYPE>& SharablePointer<TYPE>::operator=(SharablePointer<TYPE>&& other) {
		if (&other != this) {
			this->_cleanup_();
			this->_move_(other);
		}
		return *this;
	}

	template <typename TYPE>
	SharablePointer<TYPE>& SharablePointer<TYPE>::operator=(const SharablePointer<TYPE>& other) {
		if (&other != this) {
			this->_cleanup_();
			this->_copy_(other);
		}
		return *this;
	}

	template <typename TYPE>
	SharablePointer<TYPE>::~SharablePointer() {
		this->_cleanup_();
		return;
	}

	template <typename TYPE>
	SharablePointer<TYPE>::SharablePointer(TYPE instance) : record(new InstanceRecord{ 1, new TYPE(move_cast(instance)) }) {
		return;
	}

	template <typename TYPE>
	SharablePointer<TYPE>::operator TYPE* () {
		return this->access_instance();
	}

	template <typename TYPE>
	SharablePointer<TYPE>::operator const TYPE* () const {
		return this->access_instance();
	}

	template <typename TYPE>
	TYPE* SharablePointer<TYPE>::operator->() {
		return this->access_instance();
	}

	template <typename TYPE>
	const TYPE* SharablePointer<TYPE>::operator->() const {
		return this->access_instance();
	}

	template <typename TYPE>
	inline void SharablePointer<TYPE>::_move_(SharablePointer<TYPE>& other) {
		this->record = other.record;
		other.record = nullptr;
		return;
	}

	template <typename TYPE>
	inline void SharablePointer<TYPE>::_copy_(const SharablePointer<TYPE>& other) {
		if (other.record != nullptr) {
			++(other.record->number_of_handles);
		}
		this->record = other.record;
		return;
	}

	template <typename TYPE>
	inline void SharablePointer<TYPE>::_cleanup_() {
		if (this->record != nullptr) {
			--(this->record->number_of_handles);
			if (this->record->number_of_handles == 0) {
				delete this->record->instance;
				delete this->record;
			}
		}
		this->record = nullptr;
		return;
	}

	template <typename TYPE>
	inline TYPE* SharablePointer<TYPE>::access_instance() const {
		return (this->record == nullptr) ? nullptr : this->record->instance;
	}

}