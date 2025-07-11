#pragma once
#include "ProtoString.h"


namespace Proto {

	class AbstractSocket {
	public:
		virtual bool bind(const String& target, const size_t port) = 0;
		virtual bool connect(const String& target, const size_t port) = 0;
		virtual size_t peek(Array<char>& bytes) = 0;
		virtual size_t read(Array<char>& bytes) = 0;
		virtual void write(const Array<char>& bytes) = 0;
		virtual void close() = 0;
		virtual bool connected() = 0;
	protected:
	private:
	};

}