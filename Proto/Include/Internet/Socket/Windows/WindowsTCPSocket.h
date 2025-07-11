#pragma once
#include "Internet/Socket/SocketImplementation.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


namespace Proto {

	class WindowsTCPSocket : public SocketImplementation<WindowsTCPSocket> {
	public:
		WindowsTCPSocket();
		WindowsTCPSocket(WindowsTCPSocket&& other);
		WindowsTCPSocket(const WindowsTCPSocket& other) = delete;
		WindowsTCPSocket& operator=(WindowsTCPSocket&& other);
		WindowsTCPSocket& operator=(const WindowsTCPSocket& other) = delete;
		~WindowsTCPSocket();

		virtual bool bind(const String& target, const size_t port) override;
		virtual bool connect(const String& target, const size_t port) override;
		virtual WindowsTCPSocket accept() override;
		virtual size_t peek(Array<char>& bytes) override;
		virtual size_t read(Array<char>& bytes) override;
		virtual void write(const Array<char>& bytes) override;
		virtual void close() override;
		virtual bool connected() override;
	protected:
		inline void _move_(WindowsTCPSocket& other);
		inline void _copy_(const WindowsTCPSocket& other) = delete;
		inline void _cleanup_();
	private:
		WSADATA wsa_data;
		SOCKET socket;

		WindowsTCPSocket(SOCKET socket);
		inline void setup_winsock();
	};

}