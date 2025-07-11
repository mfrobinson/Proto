#pragma once
#include "Defines/Platform.h"

#ifdef WINDOWS_PLATFORM
#include "Internet/Socket/Windows/WindowsTCPSocket.h"

namespace Proto {

	typedef WindowsTCPSocket TCPSocket;

}

#else
#ifdef LINUX_PLATFORM
#include "Internet/Socket/LinuxSocket.h"

namespace Proto {

	typedef LinuxSocket Socket;

}

#endif
#endif