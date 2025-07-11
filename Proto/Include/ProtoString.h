#pragma once
#include "Memory Management/Pointers/Array.h"
#include <iostream>


namespace Proto {

	class String : public Array<char> {
	public:
		String();
		String(String&& other);
		String(const String& other);
		String& operator=(String&& other);
		String& operator=(const String& other);
		~String();

		String(long long value);
		String(unsigned long long value);

		String(const char* source);
		String(const char* source, const size_t length);
		String(const char* source, const size_t from, const size_t to);
		String reverse() const;
		String replace(const char* target, const char* with) const;

		// ==
		bool operator==(const char* literal) const;
		bool operator==(const String& other) const;

		// +
		String operator+(const char* literal) const;
		String operator+(const String& additional) const;
		String& operator+=(const String& additional);

		// *
		String operator*(const size_t count) const;
		String& operator*=(const size_t count);

	protected:
	private:
	};

	String operator+(const char* literal, const String& string);

	std::ostream& operator<<(std::ostream& os, const String& string);

}