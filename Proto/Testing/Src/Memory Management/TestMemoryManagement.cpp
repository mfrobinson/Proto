#include "Testing/Include/Memory Management/TestMemoryManagement.h"
#include "Testing/Include/Memory Management/Pointers/TestPointer.h"


namespace Proto {

	String TestMemoryManagement::name() {
		return "Test Memory Management";
	}

	bool TestMemoryManagement::execute() {
		bool passed = true;
		passed &= TestPointer().run();
		return passed;
	}

}