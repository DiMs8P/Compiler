#include "Compiler.h"

#include "Constant.h"
#include "Identificator.h"
#include "DataReader/CharsReader.h"

Compiler::Compiler(const string& inputFilePath)
{
	CharsReader reader(inputFilePath);
	program = reader.Read();
}

void Compiler::Compile()
{
	lexicalAnalyzer.Analyze(program);
}
