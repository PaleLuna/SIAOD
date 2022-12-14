#pragma once

#include <string>

class ITest
{
	public:
		virtual void Test() = 0;
		virtual std::string GetName() = 0;
};

