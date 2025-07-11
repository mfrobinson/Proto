#pragma once
#include "Defines/Platform.h"
#ifdef WINDOWS_PLATFORM
#include "Windows/Console/Formatting/WindowsConsoleFormat.h"


namespace Proto {

	class BackgroundRed : public WindowsConsoleFormat {
	public:
		void apply() const override;
	protected:
	private:
	};

}


#endif