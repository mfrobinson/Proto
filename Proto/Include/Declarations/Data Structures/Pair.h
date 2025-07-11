#pragma once
#include <type_traits>


namespace Proto {

	template <typename FORMER_TYPE, typename LATTER_TYPE>
	struct Pair {
		FORMER_TYPE key;
		LATTER_TYPE value;
		Pair();
		Pair(Pair<FORMER_TYPE, LATTER_TYPE>&& other);
		Pair(const Pair<FORMER_TYPE, LATTER_TYPE>& other) requires std::is_copy_constructible<FORMER_TYPE>::value && std::is_copy_constructible<LATTER_TYPE>::value;
		Pair(FORMER_TYPE key, LATTER_TYPE value);
		~Pair();
		Pair<FORMER_TYPE, LATTER_TYPE>& operator=(Pair<FORMER_TYPE, LATTER_TYPE>&& other);
		Pair<FORMER_TYPE, LATTER_TYPE>& operator=(const Pair<FORMER_TYPE, LATTER_TYPE>& other) requires std::is_copy_constructible<FORMER_TYPE>::value && std::is_copy_constructible<LATTER_TYPE>::value;
	};

}