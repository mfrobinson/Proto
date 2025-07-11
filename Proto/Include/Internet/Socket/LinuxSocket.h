#pragma once
#include "Defines/Platform.h"
#ifdef LINUX_PLATFORM
#include "Internet/Socket/SocketImplementation.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


namespace Proto {

	class LinuxSocket : public SocketImplementation<LinuxSocket> {
	public:
		LinuxSocket();
		LinuxSocket(LinuxSocket&& other);
		LinuxSocket(const LinuxSocket& other) = delete;
		LinuxSocket& operator=(LinuxSocket&& other);
		LinuxSocket& operator=(const LinuxSocket& other) = delete;
		~LinuxSocket();

		virtual bool bind(const String& target, const size_t port) override;
		virtual bool connect(const String& target, const size_t port) override;
		virtual LinuxSocket accept() override;
		virtual size_t peek(Array<char>& bytes) override;
		virtual size_t read(Array<char>& bytes) override;
		virtual void write(const Array<char>& bytes) override;
		virtual void close() override;
		virtual bool connected() override;
	protected:
		inline void _move_(LinuxSocket& other);
		inline void _copy_(const LinuxSocket& other) = delete;
		inline void _cleanup_();
	private:
		bool socket_is_valid;
		int socket;

		LinuxSocket(int socket);
		inline void create_socket();
		inline void bind_socket(const String& target, const size_t port);
		inline void listen_socket(const size_t queue_length);
		inline void connect_socket(const String& target, const size_t port);
	};

}


#endif