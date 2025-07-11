#include "Defines/Platform.h"
#ifdef WINDOWS_PLATFORM
#include "Windows/Console/Formatting/WindowsConsoleFormat.h"
#include <stdexcept>


namespace Proto {

	HANDLE WindowsConsoleFormat::console_handle;

	WORD WindowsConsoleFormat::background_colour = WindowsConsoleFormat::current_background();
	WORD WindowsConsoleFormat::foreground_colour = WindowsConsoleFormat::current_foreground();

	WORD WindowsConsoleFormat::current_foreground() {
		return WindowsConsoleFormat::get_console_colour() & (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}
	WORD WindowsConsoleFormat::current_background() {
		return WindowsConsoleFormat::get_console_colour() & (BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
	}

	void WindowsConsoleFormat::update() {
		if (WindowsConsoleFormat::console_handle == nullptr) {
			WindowsConsoleFormat::console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
		}
		WORD combined_colour = WindowsConsoleFormat::background_colour | WindowsConsoleFormat::foreground_colour;
		SetConsoleTextAttribute(WindowsConsoleFormat::console_handle, combined_colour);
		return;
	}

	inline WORD WindowsConsoleFormat::get_console_colour() {
		if (WindowsConsoleFormat::console_handle == nullptr) {
			WindowsConsoleFormat::console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
		}
		CONSOLE_SCREEN_BUFFER_INFO info;
		if (!GetConsoleScreenBufferInfo(WindowsConsoleFormat::console_handle, &info)) {
			throw std::runtime_error("Could not retrieve console screen buffer information!");
		}
		return info.wAttributes;
	}

	std::ostream& operator<<(std::ostream& os, const WindowsConsoleFormat& format) {
		format.apply();
		return os;
	}

}


#endif