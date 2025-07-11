#include "Testing/Include/Test.h"
#include "Defines/ConsoleText.h"
#include "Defines/ConsoleFormatting.h"
#include <iostream>


namespace Proto {

	bool Test::run() {
		std::cout << CONSOLE_TEXT_CYAN << "Performing \"" << this->name() << "\" tests..." << CONSOLE_RESET_FORMAT << NEWLINE;
		return this->result(this->execute(), this->name());
	}

	bool Test::result(const bool result, const String& test_name) {
		if (result) {
			std::cout << CONSOLE_BOLD << CONSOLE_TEXT_GREEN << "\"" << test_name << "\" passed" << CONSOLE_RESET_FORMAT << NEWLINE;
		}
		else {
			std::cout << CONSOLE_BOLD << CONSOLE_TEXT_RED << "\"" << test_name << "\" failed!" << CONSOLE_RESET_FORMAT << NEWLINE;
		}
		return result;
	}

}