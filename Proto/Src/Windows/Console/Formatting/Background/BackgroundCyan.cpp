#include "Defines/Platform.h"
#ifdef WINDOWS_PLATFORM
#include "Windows/Console/Formatting/Background/BackgroundCyan.h"
#include <wincon.h>


namespace Proto {

	void BackgroundCyan::apply() const {
		// Clear foreground colour without affecting intensity (or any other potential future flags)
		WindowsConsoleFormat::background_colour &= ~(BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
		// Apply the cyan foreground colour to the bitmask
		WindowsConsoleFormat::background_colour |= BACKGROUND_GREEN | BACKGROUND_BLUE;
		WindowsConsoleFormat::update();
		return;
	}

}


#endif