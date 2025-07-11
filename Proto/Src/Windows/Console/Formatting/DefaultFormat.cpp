#include "Defines/Platform.h"
#ifdef WINDOWS_PLATFORM
#include "Windows/Console/Formatting/DefaultFormat.h"
#include <wincon.h>
#include <iostream>


namespace Proto {

	WORD DefaultFormat::default_foreground = WindowsConsoleFormat::current_foreground();
	WORD DefaultFormat::default_background = WindowsConsoleFormat::current_background();

	void DefaultFormat::apply() const {
		WindowsConsoleFormat::foreground_colour = DefaultFormat::default_foreground;
		WindowsConsoleFormat::background_colour = DefaultFormat::default_background;
		WindowsConsoleFormat::update();
		return;
	}

}


#endif