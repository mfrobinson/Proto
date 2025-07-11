#pragma once
#include "Internet/Socket/AbstractSocket.h"


namespace Proto {

	template <typename SOCKET_CLASS>
	class SocketImplementation : public AbstractSocket {
	public:
		virtual SOCKET_CLASS accept() = 0;
	protected:
	private:
	};

}