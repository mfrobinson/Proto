#pragma once
#include "Defines/Platform.h"

#ifdef LINUX_PLATFORM
#define NEWLINE "\r\n"
#else
#ifdef WINDOWS_PLATFORM
#define NEWLINE "\n"
#endif
#endif