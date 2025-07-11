#include "Defines/Platform.h"
#ifdef WINDOWS_PLATFORM
#include "Windows/Console/Formatting/Foreground/ForegroundBlack.h"
#include <wincon.h>


namespace Proto {

	void ForegroundBlack::apply() const {
		// Clear foreground colour without affecting intensity (or any other potential future flags)
		WindowsConsoleFormat::foreground_colour &= ~(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		WindowsConsoleFormat::update();
		return;
	}

}


#endif