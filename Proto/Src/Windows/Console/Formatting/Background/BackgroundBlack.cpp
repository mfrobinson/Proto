#include "Defines/Platform.h"
#ifdef WINDOWS_PLATFORM
#include "Windows/Console/Formatting/Background/BackgroundBlack.h"
#include <wincon.h>


namespace Proto {

	void BackgroundBlack::apply() const {
		// Clear foreground colour without affecting intensity (or any other potential future flags)
		WindowsConsoleFormat::background_colour &= ~(BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
		WindowsConsoleFormat::update();
		return;
	}

}


#endif