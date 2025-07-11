#pragma once
#include "Internet/Http/HttpRequest.h"
#include "Internet/Http/HttpResponse.h"


namespace Proto {

	class HttpService {
	public:
		virtual HttpResponse serve_request(const HttpRequest& request) = 0;
	protected:
	private:
	};

}