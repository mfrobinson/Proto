#pragma once
#include "Declarations/Data Structures/Pair.h"
#include "Cast/move_cast.h"


namespace Proto {

	template <typename FORMER_TYPE, typename LATTER_TYPE>
	Pair<FORMER_TYPE, LATTER_TYPE>::Pair() : key(), value() {
		return;
	}

	template <typename FORMER_TYPE, typename LATTER_TYPE>
	Pair<FORMER_TYPE, LATTER_TYPE>::Pair(Pair<FORMER_TYPE, LATTER_TYPE>&& other) : key(move_cast(other.key)), value(move_cast(other.value)) {
		return;
	}

	template <typename FORMER_TYPE, typename LATTER_TYPE>
	Pair<FORMER_TYPE, LATTER_TYPE>::Pair(const Pair<FORMER_TYPE, LATTER_TYPE>& other) requires std::is_copy_constructible<FORMER_TYPE>::value && std::is_copy_constructible<LATTER_TYPE>::value : key(other.key), value(other.value) {
		return;
	}

	template <typename FORMER_TYPE, typename LATTER_TYPE>
	Pair<FORMER_TYPE, LATTER_TYPE>::Pair(FORMER_TYPE key, LATTER_TYPE value) : key(move_cast(key)), value(move_cast(value)) {
		return;
	}

	template <typename FORMER_TYPE, typename LATTER_TYPE>
	Pair<FORMER_TYPE, LATTER_TYPE>::~Pair() {
		return;
	}

	template <typename FORMER_TYPE, typename LATTER_TYPE>
	Pair<FORMER_TYPE, LATTER_TYPE>& Pair<FORMER_TYPE, LATTER_TYPE>::operator=(Pair<FORMER_TYPE, LATTER_TYPE>&& other) {
		this->key = move_cast(other.key);
		this->value = move_cast(other.value);
		return *this;
	}

	template <typename FORMER_TYPE, typename LATTER_TYPE>
	Pair<FORMER_TYPE, LATTER_TYPE>& Pair<FORMER_TYPE, LATTER_TYPE>::operator=(const Pair<FORMER_TYPE, LATTER_TYPE>& other) requires std::is_copy_constructible<FORMER_TYPE>::value && std::is_copy_constructible<LATTER_TYPE>::value {
		this->key = other.key;
		this->value = other.value;
		return *this;
	}

}