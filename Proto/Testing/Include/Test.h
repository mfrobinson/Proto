#pragma once
#include "ProtoString.h"


namespace Proto {

	class Test {
	public:
		bool run();
	protected:
		virtual String name() = 0;
		virtual bool execute() = 0;
		bool result(const bool result, const String& test_name);
	private:
	};

}