#include "ProtoString.h"
#include "Memory Management/find.h"
#include "Memory Management/number_of_digits.h"
#include "Memory Management/compare_memory.h"
#include "Memory Management/copy_memory.h"
#include "Cast/move_cast.h"


namespace Proto {

	String::String() : Array<char>(1, "\0") {
		return;
	}

	String::String(String&& other) : Array<char>(move_cast(other)) {
		return;
	}

	String::String(const String& other) : Array<char>(static_cast<const Array<char>&>(other)) {
		return;
	}

	String& String::operator=(String&& other) {
		Array<char>::operator=(move_cast<Array<char>>(other));
		return *this;
	}

	String& String::operator=(const String& other) {
		Array<char>::operator=(static_cast<const Array<char>&>(other));
		/*
		if (&other != this) {
			Array<char>::_cleanup_();
			if (other.length() == 0) {
				this->memory = nullptr;
			}
			else {
				this->memory = new char[other.length()];
				for (size_t i = 0; i < other.length(); ++i) {
					this->memory[i] = other.memory[i];
				}
			}
		}
		*/
		return *this;
	}

	String::~String() {
		return;
	}

	String::String(unsigned long long value) : Array<char>(number_of_digits(value) + 1) {
		size_t number_of_digits = this->length() - 1;
		for (size_t i = 0; i < number_of_digits; ++i) {
			this->memory[this->length() - i - 2] = (value % 10) + '0';
			value /= 10;
		}
		this->memory[this->length() - 1] = '\0';
		return;
	}

	String::String(long long value) : Array<char>(number_of_digits(value) + 1) {
		size_t number_of_digits = this->length() - 1;
		if (value < 0) {
			this->memory[0] = '-';
			value *= -1;
			--number_of_digits;
		}
		for (size_t i = 0; i < number_of_digits; ++i) {
			this->memory[this->length() - i - 2] = (value % 10) + '0';
			value /= 10;
		}
		this->memory[this->length() - 1] = '\0';
		return;
	}

	String::String(const char* source) : Array<char>(find<char>(source, '\0') + 1, source) {
		return;
	}

	String::String(const char* source, const size_t length) : Array<char>(length + 1) {
		copy_memory(source, this->memory, length);
		this->memory[length] = '\0';
		return;
	}

	String::String(const char* source, const size_t from, const size_t to) : Array<char>() {
		if (from > to) {
			throw std::runtime_error("Values for 'from' and 'to' do not create a valid boundary!");
		}
		Array<char>::operator=(Array<char>(to - from, source + from));
		return;
	}
	//		size_t length();
	//		operator char* ();
	//		operator const char* () const;
	String String::reverse() const {
		String result;
		size_t length = this->length();
		static_cast<Array<char>&>(result) = Array<char>(length);
		for (size_t i = 0; i < length - 1; ++i) {
			result[i] = *this[length - i];
		}
		result[length] = '\0';
		return result;
	}

	String String::replace(const char* target, const char* with) const {
		size_t target_length = find(target, '\0');
		size_t with_length = find(with, '\0');
		if (this->length() <= target_length) {
			return *this;
		}
		String result;
		size_t last_index = 0;
		size_t i = 0;
		size_t modifier = (target_length == 0) ? 1 : 0;
		for (; i < this->length() - target_length - modifier; ++i) {
			if (compare_memory(this->memory + i, target, target_length)) {
				result += String(this->memory + last_index, i - last_index);
				result += String(with, with_length);
				last_index = i + target_length + modifier;
				i += target_length + (modifier - 1);
			}
		}
		result += String(this->memory + last_index, this->length() - last_index - 1);
		return result;
	}

	bool String::operator==(const String& other) const {
		if (this->length() != other.length()) {
			return false;
		}
		return compare_memory(this->memory, other.memory, this->length());
	}

	bool String::operator==(const char* literal) const {
		return compare_memory(this->memory, literal, this->length());
	}

	String String::operator+(const char* literal) const {
		String result;
		size_t literal_length = find(literal, '\0');
		Array<char> raw_array(this->length() + literal_length);
		copy_memory<char>(this->memory, raw_array, this->length());
		copy_memory<char>(literal, raw_array + this->length() - 1, literal_length);
		raw_array[this->length() + literal_length - 1] = '\0';
		static_cast<Array<char>&>(result) = move_cast<Array<char>>(raw_array);
		return result;
	}

	String String::operator+(const String& additional) const {
		String result;
		size_t additional_length = additional.length() - 1;
		Array<char> raw_array(this->length() + additional_length);
		copy_memory<char>(this->memory, raw_array, this->length());
		copy_memory<char>(additional.memory, raw_array + this->length() - 1, additional_length);
		raw_array[this->length() + additional_length - 1] = '\0';
		static_cast<Array<char>&>(result) = move_cast<Array<char>>(raw_array);
		return result;
	}

	bool operator==(const String& lhs, const String& rhs) {
		return lhs.operator==(rhs);
	}

	String& String::operator+=(const String& additional) {
		Array<char> extended = Array<char>(this->length() + additional.length() - 1);
		copy_memory<char>(this->memory, extended, this->length() - 1);
		copy_memory<char>(additional.memory, extended + this->length() - 1, additional.length());
		static_cast<Array<char>&>(*this) = move_cast(extended);
		return *this;
	}

	String String::operator*(const size_t count) const {
		String result;
		size_t copyable_length = this->length() - 1;
		size_t total_length = copyable_length * count;
		Array<char> repeated = Array<char>(total_length + 1);
		for (size_t i = 0; i < count; ++i) {
			copy_memory(this->memory, repeated + copyable_length * i, copyable_length);
		}
		repeated[total_length] = '\0';
		static_cast<Array<char>&>(result) = move_cast(repeated);
		return result;
	}
	String& String::operator*=(const size_t count) {
		size_t copyable_length = this->length() - 1;
		size_t total_length = copyable_length * count;
		Array<char> repeated = Array<char>(total_length + 1);
		for (size_t i = 0; i < count; ++i) {
			copy_memory(this->memory, repeated + copyable_length * i, copyable_length);
		}
		repeated[total_length] = '\0';
		static_cast<Array<char>&>(*this) = move_cast(repeated);
		return *this;
	}

	String operator+(const char* literal, const String& string) {
		return String(literal) + (const char*)string;
	}

	std::ostream& operator<<(std::ostream& os, const String& string) {
		if ((const char*)string != nullptr) {
			os << (const char*)string;
		}
		return os;
	}

}