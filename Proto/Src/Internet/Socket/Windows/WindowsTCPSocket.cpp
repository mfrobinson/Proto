#include "Internet/Socket/Windows/WindowsTCPSocket.h"
#include "Memory Management/zero_memory.h"
#include <stdexcept>


namespace Proto {

	WindowsTCPSocket::WindowsTCPSocket() : socket(INVALID_SOCKET) {
		this->setup_winsock();
		return;
	}

	WindowsTCPSocket::WindowsTCPSocket(WindowsTCPSocket&& other) {
		this->setup_winsock();
		this->_move_(other);
		return;
	}

	WindowsTCPSocket& WindowsTCPSocket::operator=(WindowsTCPSocket&& other) {
		if (&other != this) {
			this->_cleanup_();
			this->_move_(other);
		}
		return *this;
	}

	WindowsTCPSocket::~WindowsTCPSocket() {
		this->_cleanup_();
		WSACleanup();
		return;
	}

	bool WindowsTCPSocket::bind(const String& target, const size_t port) {
		if (this->socket != INVALID_SOCKET) {
			throw std::runtime_error("Cannot bind on an already connected socket!");
		}
		struct addrinfo* result = nullptr, * ptr = nullptr, hints;
		zero_memory(&hints, 1);
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;
		hints.ai_flags = AI_PASSIVE;

		int result_code = getaddrinfo(target, String(port), &hints, &result);
		if (result_code != 0) {
			throw std::runtime_error("getaddrinfo call failed!");
		}

		this->socket = ::socket(result->ai_family, result->ai_socktype, result->ai_protocol);
		if (this->socket == INVALID_SOCKET) {
			throw std::runtime_error("socket call failed!");
		}

		result_code = ::bind(this->socket, result->ai_addr, result->ai_addrlen);
		if (result_code == SOCKET_ERROR) {
			this->_cleanup_();
			throw std::runtime_error("bind call failed!");
		}

		freeaddrinfo(result);

		result_code = ::listen(this->socket, SOMAXCONN);
		if (result_code == SOCKET_ERROR) {
			this->_cleanup_();
			throw std::runtime_error("listen call failed!");
		}

		return true;
	}

	bool WindowsTCPSocket::connect(const String& target, const size_t port) {
		if (this->socket != INVALID_SOCKET) {
			throw std::runtime_error("Cannot bind on an already connected socket!");
		}

		struct addrinfo* result = nullptr, * ptr = nullptr, hints;
		zero_memory(&hints, 1);
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;

		int result_code = getaddrinfo(target, String(port), &hints, &result);
		if (result_code != 0) {
			throw std::runtime_error("getaddrinfo call failed!");
		}

		for (ptr = result; ptr != nullptr; ptr = ptr->ai_next) {
			this->socket = ::socket(result->ai_family, result->ai_socktype, result->ai_protocol);
			if (this->socket == INVALID_SOCKET) {
				throw std::runtime_error("socket call failed!");
			}

			result_code = ::connect(this->socket, ptr->ai_addr, ptr->ai_addrlen);
			if (result_code == SOCKET_ERROR) {
				this->_cleanup_();
				this->socket = INVALID_SOCKET;
			}
			else {
				break;
			}
		}

		freeaddrinfo(result);

		if (this->socket == INVALID_SOCKET) {
			return false;
		}

		return true;
	}

	WindowsTCPSocket WindowsTCPSocket::accept() {
		if (this->socket == INVALID_SOCKET) {
			throw std::runtime_error("Cannot read on an unconnected socket!");
		}

		SOCKET accepted_socket = ::accept(this->socket, nullptr, nullptr);
		if (accepted_socket == INVALID_SOCKET) {
			this->_cleanup_();
			throw std::runtime_error("accept call failed!");
		}

		return WindowsTCPSocket(accepted_socket);
	}

	size_t WindowsTCPSocket::peek(Array<char>& bytes) {
		if (this->socket == INVALID_SOCKET) {
			throw std::runtime_error("Cannot read on an unconnected socket!");
		}
		int result_code = ::recv(this->socket, bytes, bytes.length(), MSG_PEEK);
		if (result_code == 0) {
			this->_cleanup_();
		}
		else if (result_code < 0) {
			throw std::runtime_error("recv call failed!");
		}
		return result_code;
	}

	size_t WindowsTCPSocket::read(Array<char>& bytes) {
		if (this->socket == INVALID_SOCKET) {
			throw std::runtime_error("Cannot read on an unconnected socket!");
		}
		int result_code = ::recv(this->socket, bytes, bytes.length(), 0);
		if (result_code == 0) {
			this->_cleanup_();
		}
		else if (result_code < 0) {
			throw std::runtime_error("recv call failed!");
		}
		return result_code;
	}

	void WindowsTCPSocket::write(const Array<char>& bytes) {
		if (this->socket == INVALID_SOCKET) {
			throw std::runtime_error("Cannot write on an unconnected socket!");
		}
		int result_code = ::send(this->socket, bytes, bytes.length(), 0);
		if (result_code == 0) {
			this->_cleanup_();
		}
		else if (result_code < 0) {
			throw std::runtime_error("send call failed!");
		}
		return;
	}

	void WindowsTCPSocket::close() {
		this->_cleanup_();
		return;
	}

	bool WindowsTCPSocket::connected() {
		return this->socket != INVALID_SOCKET;
	}

	inline void WindowsTCPSocket::_move_(WindowsTCPSocket& other) {
		this->wsa_data = (WSAData&&)other.wsa_data;
		this->socket = (SOCKET&&)other.socket;
		other.wsa_data = WSAData();
		other.socket = INVALID_SOCKET;
		return;
	}

	inline void WindowsTCPSocket::_cleanup_() {
		::shutdown(this->socket, SD_BOTH);
		::closesocket(this->socket);
		this->socket = INVALID_SOCKET;
		return;
	}

	WindowsTCPSocket::WindowsTCPSocket(SOCKET socket) : socket(socket) {
		this->setup_winsock();
		return;
	}

	inline void WindowsTCPSocket::setup_winsock() {
		int result_code = WSAStartup(MAKEWORD(2,2), &this->wsa_data);
		if (result_code != 0) {
			throw std::runtime_error("WSAStartup call failed!");
		}
		return;
	}

}