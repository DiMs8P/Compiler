#pragma once
#include <string>

using namespace std;

struct Identificator
{
	string name;
	int type = 0;
	int value = 0;

	bool operator==(Identificator const& otherToken) const { return (name == otherToken.name) && (type == otherToken.type && (value == otherToken.value)); }
};
