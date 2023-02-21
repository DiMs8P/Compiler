#pragma once
#include "Token.h"
#include <string>
#include "DataTable/PersistentTable.h"

struct Token;
using namespace std;

class LexicalAnalyzer
{
public:
	friend class Compiler;

	LexicalAnalyzer();
	void Analyze(const vector<char>& program);

protected:
	vector<PersistentTable<string>> StringTables;
};

