#include "Internet/Server/HttpServer.h"
#include "Memory Management/contains.h"
#include "Memory Management/find.h"
#include "Memory Management/find_last.h"
#include "Storage Management/FileReader.h"
#include "Storage Management/FileWriter.h"
#include <thread>
//#include "Scripting/PHP/PhpExecutor.h"

#include <iostream>
#include <Pdh.h>
#pragma comment(lib, "pdh.lib")


namespace Proto {

	HttpServer::HttpServer() {
		return;
	}

	HttpServer::~HttpServer() {
		return;
	}

	void HttpServer::deploy(const String& address, const size_t port) {
		std::thread server_service(&HttpServer::run, this, address, port);
		server_service.detach();
		return;
	}

	void HttpServer::on_run() {
		return;
	}

	String HttpServer::translate_target(const String& original) {
		if (original == "/") {
			return "./index.htm";
		}
		return "." + original;
	}

	void HttpServer::run(const String address, const size_t port) {
		if (!this->master_socket.bind(address, port)) {
			return;
		}
		this->running = true;
		this->on_run();
		while (this->running) {
			TCPSocket client = this->master_socket.accept();
			if (client.connected()) {
				std::thread client_service(&HttpServer::handle_client, this, (TCPSocket&&)client);
				client_service.detach();
			}
		}
		return;
	}

	void HttpServer::stop() {
		this->running = false;
		return;
	}

	void HttpServer::handle_client(TCPSocket client) {
		Array<char> request = this->get_request_header(client);
		while (this->running && client.connected()) {
			this->service_request(client, request);
			client.close();
		}
		client.close();
		return;
	}

	#define MSG_PEEK_BLOCK_SIZE 1024
	#define HTTP_PACKET_DELIM "\r\n\r\n"
	#define HTTP_PACKET_DELIM_LENGTH find<char>(HTTP_PACKET_DELIM, '\0')
	#define MSG_CUTOFF_POINT 10240
	Array<char> HttpServer::get_request_header(TCPSocket& client) {
		Array<char> packet;
		Array<char> msg_peek = Array<char>(MSG_PEEK_BLOCK_SIZE);
		while (msg_peek.length() < MSG_CUTOFF_POINT && client.connected()) {
			size_t result = client.peek(msg_peek);
			if (contains<char>(msg_peek, HTTP_PACKET_DELIM, HTTP_PACKET_DELIM_LENGTH, result)) {
				packet = Array<char>(find<char>(msg_peek, HTTP_PACKET_DELIM, HTTP_PACKET_DELIM_LENGTH) + HTTP_PACKET_DELIM_LENGTH);
				client.read(packet);
				return packet;
			}
			// Only upsize if more space is required
			// Client may send request in pieces, which the server should handle correctly
			if (result == msg_peek.length()) {
				msg_peek = Array<char>(msg_peek.length() + MSG_PEEK_BLOCK_SIZE);
			}
		}
		client.close();
		return packet;
	}

	HttpRequest HttpServer::parse_request(TCPSocket& client, const Array<char>& request) {
		HttpRequest parsed_request{};
		size_t bytes_left = request.length();
		const char* request_cursor = request;
		parsed_request.method = this->read_until_and_exclude(request_cursor, bytes_left, ' ');
		parsed_request.target = this->read_until_and_exclude(request_cursor, bytes_left, ' ');
		parsed_request.version = this->read_until_and_exclude(request_cursor, bytes_left, "\r\n", find("\r\n", '\0'));

		this->replace_url_escape_codes(parsed_request);

		if (contains<char>(parsed_request.target, '?', parsed_request.target.length())) {
			String process = move_cast(parsed_request.target);
			size_t index_of_question_mark = find<char>(process, '?');
			parsed_request.target = String(process, index_of_question_mark);
			const char* raw_arguments = (const char*)process + index_of_question_mark + 1;

			size_t bytes_left = process.length() - index_of_question_mark - 2;
			while (contains(raw_arguments, '=', bytes_left)) {
				size_t arg_key_length = find(raw_arguments, '=');
				String arg_key(raw_arguments, arg_key_length);
				raw_arguments += arg_key_length + 1;
				bytes_left -= arg_key_length + 1;
				String arg_value;
				if (contains(raw_arguments, '&', bytes_left)) {
					size_t arg_value_length = find(raw_arguments, '&');
					arg_value = String(raw_arguments, arg_value_length);
					raw_arguments += arg_value_length + 1;
					bytes_left -= arg_value_length + 1;
				}
				else {
					arg_value = String(raw_arguments, bytes_left);
					raw_arguments += bytes_left;
					bytes_left -= bytes_left;
				}
				parsed_request.request_arguments.set(move_cast(arg_key), move_cast(arg_value));
			}
		}

		size_t body_length = 0;
		while (contains(request_cursor, ':', bytes_left)) {
			// Read in the header key
			String key = this->read_until_and_exclude(request_cursor, bytes_left, ':');
			// Skip whitespace
			while (*request_cursor == ' ' && bytes_left > 0) {
				++request_cursor;
				--bytes_left;
			}

			if (!contains(request_cursor, "\r\n", 2, bytes_left)) {
				// !! MALFORMAT !!
			}
			// Read in the header value
			String value = this->read_until_and_exclude(request_cursor, bytes_left, "\r\n", 2);
			parsed_request.headers.append(HttpHeader{ key, value });

			if (key == "Content-Length") {
				body_length = 0;
				for (size_t i = 0; i < value.length(); ++i) {
					if (value[value.length() - 1 - i] >= '0' && value[value.length() - 1 - i] <= '9') {
						body_length *= 10;
						body_length += value[value.length() - 1 - i] - '0';
					}
				}
			}

			/*
			parsed_request.version = key;
			request_cursor += parsed_request.version.length();
			bytes_left -= parsed_request.version.length();
			*/
		}
		if (body_length > 0) {
			Array<char> body(body_length);
			client.read(body);
			parsed_request.body = String(body, body_length);
		}
		parsed_request.target = this->translate_target(parsed_request.target);
		return parsed_request;
	}

	inline String HttpServer::read_until_and_exclude(const char*& request_cursor, size_t& bytes_left, const char delim) {
		String result;
		if (contains(request_cursor, delim, bytes_left)) {
			result = String(request_cursor, find(request_cursor, delim));
			request_cursor += result.length();
			bytes_left -= result.length();
		}
		return result;
	}
	inline String HttpServer::read_until_and_exclude(const char*& request_cursor, size_t& bytes_left, const char* delim, const size_t delim_length) {
		String result;
		if (contains(request_cursor, delim, delim_length, bytes_left)) {
			result = String(request_cursor, find(request_cursor, delim, delim_length));
			request_cursor += (result.length() - 1) + delim_length;
			bytes_left -= (result.length() - 1) + delim_length;
		}
		return result;
	}


	void HttpServer::service_request(TCPSocket& client, const Array<char>& request) {
		HttpRequest parsed_request = this->parse_request(client, request);
		HttpResponse response = this->serve_request(parsed_request);
		this->send_response(client, response);
		return;
	}
	HttpResponse HttpServer::serve_request(const HttpRequest& request) {
		HttpResponse response{};
		if (request.method == "GET") {
			String file_extension("html");
			if (contains<char>(request.target, '.', request.target.length())) {
				size_t index_of_last_dot = find_last<char>(request.target, '.', request.target.length());
				file_extension = String((const char*)request.target + index_of_last_dot + 1, request.target.length() - index_of_last_dot - 1);
			}
			FileReader resource_reader;
			if (resource_reader.open(request.target)) {
				response.version = request.version;
				response.status_code = "200";
				response.status_text = "OK";
				if (file_extension == "htm" || file_extension == "html") {
					response.headers.append(HttpHeader{ "Content-Type", "text/html; charset=ascii" });
				}
				else {
					response.headers.append(HttpHeader{ "Content-Type", "text/unknown" });
				}
				response.body = resource_reader.read_all();
				return response;
			}
		}
		// Catch all 404
		// INSERT RETURN IF OTHER RESPONSE APPLIES!
		response.version = request.version;
		response.status_code = "404";
		response.status_text = "NOT FOUND";
		return response;
	}

	void HttpServer::send_response(TCPSocket& client, const HttpResponse& response) {
		this->send_raw_string(client, response.version);
		client.write(' ');
		this->send_raw_string(client, response.status_code);
		client.write(' ');
		this->send_raw_string(client, response.status_text);
		client.write({ '\r', '\n' });
		for (size_t i = 0; i < response.headers.length(); ++i) {
			this->send_header(client, response.headers.get(i));
		}
		if (response.body.length() > 1) {
			this->send_header(client, HttpHeader{ "Content-Length", response.body.length() - 1 });
		}
		client.write({ '\r', '\n' });
		if (response.body.length() > 1) {
			this->send_raw_string(client, response.body);
		}
		return;
	}

	inline void HttpServer::send_raw_string(TCPSocket& client, const String& str) {
		client.write(Array<char>(str.length() - 1, str));
		return;
	}

	inline void HttpServer::send_header(TCPSocket& client, const HttpHeader& header) {
		this->send_raw_string(client, header.type);
		client.write({ ':', ' ' });
		this->send_raw_string(client, header.value);
		client.write({ '\r', '\n' });
		return;
	}

	inline void HttpServer::replace_url_escape_codes(HttpRequest& request) {
		request.target = request.target.replace("%20", " ");
		request.target = request.target.replace("%3C", "<");
		request.target = request.target.replace("%3E", ">");
		request.target = request.target.replace("%23", "#");
		request.target = request.target.replace("%2B", "+");
		request.target = request.target.replace("%7B", "{");
		request.target = request.target.replace("%7D", "}");
		request.target = request.target.replace("%7C", "|");
		request.target = request.target.replace("%5C", "\\");
		request.target = request.target.replace("%5E", "^");
		request.target = request.target.replace("%7E", "~");
		request.target = request.target.replace("%5B", "[");
		request.target = request.target.replace("%5D", "]");
		request.target = request.target.replace("%60", "'");
		request.target = request.target.replace("%3B", ";");
		request.target = request.target.replace("%2F", "/");
		request.target = request.target.replace("%3F", "?");
		request.target = request.target.replace("%3A", ":");
		request.target = request.target.replace("%40", "@");
		request.target = request.target.replace("%3D", "=");
		request.target = request.target.replace("%26", "&");
		request.target = request.target.replace("%24", "$");
		request.target = request.target.replace("%25", "%");
		return;
	}

}