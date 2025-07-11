#pragma once
#include "Defines/Platform.h"
#ifdef WINDOWS_PLATFORM
#include "Windows/Console/Formatting/WindowsConsoleFormat.h"


namespace Proto {

	class DefaultFormat : public WindowsConsoleFormat {
	public:
		void apply() const override;
	protected:
	private:
		static WORD default_foreground;
		static WORD default_background;
	};

}


#endif