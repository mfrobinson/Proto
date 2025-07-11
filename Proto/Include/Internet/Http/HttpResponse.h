#pragma once
#include "Internet/Http/HttpHeader.h"
#include "Data Structures/List/ArrayList.h"


namespace Proto {

	struct HttpResponse {
		String version;
		String status_code;
		String status_text;
		ArrayList<HttpHeader> headers;
		String body;
	};

}