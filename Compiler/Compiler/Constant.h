#pragma once
#include <limits.h>

struct Constant
{
	int value = INT_MAX;
	int type = 0;

	bool operator==(Constant const& otherConstant) const { return (value == otherConstant.value) && (type == otherConstant.type); }
};
