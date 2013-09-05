#include "test/test.h"

#include <cstdio>

#define PASS 1
#define FAIL 0


short assert(int result, std::string message)
{
	if (result) {
		std::cout << message << ":PASS" << std::endl;
		return PASS;
	} else {
		std::cout << message << ":FAIL" << std::endl;
		return FAIL;
	}
}
