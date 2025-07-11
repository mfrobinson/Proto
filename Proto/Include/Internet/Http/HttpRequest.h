#pragma once
#include "Internet/Http/HttpHeader.h"
#include "Data Structures/List/ArrayList.h"
#include "Data Structures/Dictionary/ArrayDictionary.h"


namespace Proto {

	struct HttpRequest {
		String method;
		String target;
		String version;
		ArrayDictionary<String,String> request_arguments;
		ArrayList<HttpHeader> headers;
		String body;
	};

}