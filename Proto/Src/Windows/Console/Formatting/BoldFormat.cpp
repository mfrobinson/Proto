#include "Defines/Platform.h"
#ifdef WINDOWS_PLATFORM
#include "Windows/Console/Formatting/BoldFormat.h"
#include <wincon.h>
#include <cwchar>


namespace Proto {

	void BoldFormat::apply() const {
		WindowsConsoleFormat::foreground_colour ^= FOREGROUND_INTENSITY;
		WindowsConsoleFormat::update();
		return;
	}

}


#endif