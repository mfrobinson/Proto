#include "Testing/Include/TestProto.h"
#include "Testing/Include/Memory Management/TestMemoryManagement.h"


namespace Proto {

	String TestProto::name() {
		return "Test All";
	}

	bool TestProto::execute() {
		bool passed = true;
		passed &= TestMemoryManagement().run();
		return passed;
	}

}