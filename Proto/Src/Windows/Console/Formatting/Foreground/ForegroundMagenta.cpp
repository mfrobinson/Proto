#include "Defines/Platform.h"
#ifdef WINDOWS_PLATFORM
#include "Windows/Console/Formatting/Foreground/ForegroundMagenta.h"
#include <wincon.h>


namespace Proto {

	void ForegroundMagenta::apply() const {
		// Clear foreground colour without affecting intensity (or any other potential future flags)
		WindowsConsoleFormat::foreground_colour &= ~(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		// Apply the green foreground colour to the bitmask
		WindowsConsoleFormat::foreground_colour |= FOREGROUND_RED | FOREGROUND_BLUE;
		WindowsConsoleFormat::update();
		return;
	}

}


#endif