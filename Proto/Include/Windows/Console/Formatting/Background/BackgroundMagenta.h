#pragma once
#include "Defines/Platform.h"
#ifdef WINDOWS_PLATFORM
#include "Windows/Console/Formatting/WindowsConsoleFormat.h"


namespace Proto {

	class BackgroundMagenta : public WindowsConsoleFormat {
	public:
		void apply() const override;
	protected:
	private:
	};

}


#endif