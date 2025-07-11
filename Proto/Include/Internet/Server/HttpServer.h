#pragma once
#include "Internet/Server/HttpService.h"
#include "Internet/Socket/Socket.h"
#include "ProtoString.h"
#include "Data Structures/List/ArrayList.h"
#include "Internet/Http/HttpHeader.h"


namespace Proto {

	class HttpServer : protected HttpService {
	public:
		HttpServer();
		HttpServer(HttpServer&& other) = delete;
		HttpServer(const HttpServer& other) = delete;
		HttpServer& operator=(HttpServer&& other) = delete;
		HttpServer& operator=(const HttpServer& other) = delete;
		~HttpServer();

		void deploy(const String& address, const size_t port);
		void run(const String address, const size_t port);
		void stop();
	protected:
		bool running;

		virtual void on_run();
		virtual String translate_target(const String& original);
		virtual HttpResponse serve_request(const HttpRequest& request) override;
	private:
		TCPSocket master_socket;

		void handle_client(TCPSocket client);
		Array<char> get_request_header(TCPSocket& client);
		HttpRequest parse_request(TCPSocket& client, const Array<char>& request);

		inline String read_until_and_exclude(const char*& request_cursor, size_t& bytes_left, const char delim);
		inline String read_until_and_exclude(const char*& request_cursor, size_t& bytes_left, const char* delim, const size_t delim_length);

		void service_request(TCPSocket& client, const Array<char>& request);

		void send_response(TCPSocket& client, const HttpResponse& response);
		inline void send_raw_string(TCPSocket& client, const String& str);
		inline void send_header(TCPSocket& client, const HttpHeader& header);

		inline void replace_url_escape_codes(HttpRequest& request);
	};

}