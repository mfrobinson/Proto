#include "Defines/Platform.h"
#ifdef LINUX_PLATFORM
#include "Internet/Socket/LinuxSocket.h"
#include "Memory Management/zero_memory.h"
#include <arpa/inet.h>


namespace Proto {

	LinuxSocket::LinuxSocket() : socket(0), socket_is_valid(false) {
		return;
	}

	LinuxSocket::LinuxSocket(LinuxSocket&& other) {
		this->_move_(other);
		return;
	}

	LinuxSocket& LinuxSocket::operator=(LinuxSocket&& other) {
		if (&other != this) {
			this->_cleanup_();
			this->_move_(other);
		}
		return *this;
	}

	LinuxSocket::~LinuxSocket() {
		this->_cleanup_();
	}

	bool LinuxSocket::bind(const String& target, const size_t port) {
		if (this->socket_is_valid) {
			throw std::runtime_error("Cannot bind on an already connected socket!");
		}

		this->create_socket();
		this->bind_socket(target port);
		this->listen_socket(SO_MAXCONN);

		return true;
	}

	bool LinuxSocket::connect(const String& target, const size_t port) {
		if (this->socket_is_valid) {
			throw std::runtime_error("Cannot connect on an already connected socket!");
		}

		this->create_socket();
		this->connect_socket(target port);

		return true;
	}

	LinuxSocket LinuxSocket::accept() {
		if (this->socket_is_valid) {
			return LinuxSocket(::accept(this->socket, nullptr, nullptr));
		}
		return LinuxSocket();
	}

	size_t LinuxSocket::peek(Array<char>& bytes) {
		if (this->socket_is_valid) {
			return ::recv(this->socket, bytes, bytes.length(), MSG_PEEK);
		}
		return 0;
	}

	size_t LinuxSocket::read(Array<char>& bytes) {
		if (this->socket_is_valid) {
			return ::read(this->socket, bytes, bytes.length());
		}
		return 0;
	}

	void LinuxSocket::write(const Array<char>& bytes) {
		if (this->socket_is_valid) {
			::write(this->socket, bytes, bytes.length());
		}
		return;
	}

	void LinuxSocket::close() {
		if (this->socket_is_valid) {
			::shutdown(this->socket, SHUT_RDWR);
			::close(this->socket);
			this->socket_is_valid = false;
		}
		return;
	}

	bool LinuxSocket::connected() {
		return this->socket_is_valid;
	}

	inline void LinuxSocket::_move_(LinuxSocket& other) {
		this->socket = other.socket;
		this->socket_is_valid = other.socket_is_valid;
		other.socket = 0;
		other.socket_is_valid = false;
		return;
	}

	inline void LinuxSocket::_cleanup_() {
		this->close();
		return;
	}

	LinuxSocket::LinuxSocket(int socket) : socket(socket), socket_is_valid(true) {
		return;
	}

	inline void LinuxSocket::create_socket() {
		this->socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (this->socket == -1) {
			throw std::runtime_error("socket call failed!");
		}

		int reuse = 1;
		int result_code = ::setsockopt(this->socket, SOL_SOCKET, SO_REUSEADDR, (void*)&reuse, sizeof(reuse));
		if (result_code == -1) {
			throw std::runtime_error("setsockopt call failed!");
		}
		return;
	}

	inline void LinuxSocket::bind_socket(const String& target, const size_t port) {
		struct sockaddr_in addr;
		zero_memory(&addr, 1);
		addr.sin_family = AF_INET;
		inet_aton(target, (struct in_addr*)&addr.sin_addr.s_addr);
		addr.sin_port = htonl((uint32_t)port);

		int result_code = ::bind(this->socket, (struct sockaddr*)&addr, sizeof(addr));
		if (result_code == -1) {
			this->_cleanup_();
			throw std::runtime_error("bind call failed!");
		}
		return;
	}

	inline void LinuxSocket::listen_socket(const size_t queue_length) {
		int result_code = ::listen(this->socket, 1);
		if (result_code == -1) {
			this->_cleanup_();
			throw std::runtime_error("listen call failed!");
		}
		this->socket_is_valid = true;
		return;
	}

	inline void LinuxSocket::connect_socket(const String& target, const size_t port) {
		struct sockaddr_in addr;
		zero_memory(&addr, 1);
		addr.sin_family = AF_INET;
		inet_aton(target, (struct in_addr*)&addr.sin_addr.s_addr);
		addr.sin_port = htonl((uint32_t)port);

		int result_code = ::connect(this->socket, (struct sockaddr*)&addr, sizeof(addr));
		if (result_code == -1) {
			this->_cleanup_();
			throw std::runtime_error("connect call failed!");
		}
		return;
	}

}


#endif