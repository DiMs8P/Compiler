#pragma once
#include <map>
#include <string>
#include "DataTable/PersistentTable.h"

struct Token;
using namespace std;

class LexicalAnalyzer
{
public:
	friend class Compiler;

protected:
	void Init();
	void Analyze(vector<char> program);

	vector<PersistentTable<string>> StringTables;
};

