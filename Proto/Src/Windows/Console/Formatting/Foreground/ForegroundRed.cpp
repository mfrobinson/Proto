#include "Defines/Platform.h"
#ifdef WINDOWS_PLATFORM
#include "Windows/Console/Formatting/Foreground/ForegroundRed.h"
#include <wincon.h>


namespace Proto {

	void ForegroundRed::apply() const {
		// Clear foreground colour without affecting intensity (or any other potential future flags)
		WindowsConsoleFormat::foreground_colour &= ~(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		// Apply the red foreground colour to the bitmask
		WindowsConsoleFormat::foreground_colour |= FOREGROUND_RED;
		WindowsConsoleFormat::update();
		return;
	}

}


#endif