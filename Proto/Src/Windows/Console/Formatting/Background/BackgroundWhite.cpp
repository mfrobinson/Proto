#include "Defines/Platform.h"
#ifdef WINDOWS_PLATFORM
#include "Windows/Console/Formatting/Background/BackgroundWhite.h"
#include <wincon.h>


namespace Proto {

	void BackgroundWhite::apply() const {
		// Clear foreground colour without affecting intensity (or any other potential future flags)
		WindowsConsoleFormat::background_colour &= ~(BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
		// Apply the green foreground colour to the bitmask
		WindowsConsoleFormat::background_colour |= BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
		WindowsConsoleFormat::update();
		return;
	}

}


#endif