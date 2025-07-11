#pragma once
#include "Defines/Platform.h"
#ifdef WINDOWS_PLATFORM
#include <Windows.h>
#include <ostream>


namespace Proto {

	class WindowsConsoleFormat {
	public:
		virtual void apply() const = 0;
	protected:
		static WORD background_colour;
		static WORD foreground_colour;
		static void update();

		static WORD current_foreground();
		static WORD current_background();
	private:
		static HANDLE console_handle;
		static inline WORD get_console_colour();
	};

	std::ostream& operator<<(std::ostream& os, const WindowsConsoleFormat& colour);

}


#endif