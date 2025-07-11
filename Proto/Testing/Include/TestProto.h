#pragma once
#include "Testing/Include/Test.h"


namespace Proto {

	class TestProto : public Test {
	public:
		virtual String name() override;
		virtual bool execute() override;
	protected:
	private:
	};

}