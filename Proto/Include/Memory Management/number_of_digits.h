#pragma once
#include "Declarations/Memory Management/number_of_digits.h"
#include <math.h>


namespace Proto {

	size_t number_of_digits(const long long value) {
		if (value == 0) {
			return 1;
		}
		return (value < 0) ? log10(value * -1) + 2 : log10(value) + 1;
	}

	size_t number_of_digits(const unsigned long long value) {
		if (value == 0) {
			return 1;
		}
		return log10(value) + 1;
	}

}