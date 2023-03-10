#pragma once
#include <string>
#include <vector>
#include "LexicalAnalyzer.h"
#include "SyntacticalAnalyzer.h"

class Compiler
{
public:
	Compiler(const string& inputFilePath);
	void Compile();

private:
	SyntacticalAnalyzer syntacticalAnalyzer;
	LexicalAnalyzer lexicalAnalyzer;

	vector<char> program;
};

