#include "Compiler.h"
#include "DataReader/CharsReader.h"

Compiler::Compiler(const string& inputFilePath)
{
	CharsReader reader(inputFilePath);
	program = reader.Read();

	lexicalAnalyzer.Init();
}

void Compiler::Compile()
{
	lexicalAnalyzer.Analyze(program);
	
}
