#pragma once

struct Constant
{
	int value = 0;
	int type = 0;

	bool operator==(Constant const& otherConstant) const { return (value == otherConstant.value) && (type == otherConstant.type); }
};
