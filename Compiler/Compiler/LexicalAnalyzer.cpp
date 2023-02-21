#include "LexicalAnalyzer.h"
#include "DataReader/CharsReader.h"
#include "DataReader/StringsReader.h"

void LexicalAnalyzer::Init()
{
	StringsReader readerString(R"(InputData\word.txt)");
	PersistentTable<string> StringTable;
	StringTable.Load(readerString);
	StringTables.push_back(StringTable);

	readerString.SetFilePath(R"(InputData\razdelitelb.txt)");
	StringTable.Load(readerString);
	StringTables.push_back(StringTable);

	readerString.SetFilePath(R"(InputData\znak.txt)");
	StringTable.Load(readerString);
	StringTables.push_back(StringTable);
}

void LexicalAnalyzer::Analyze(vector<char> program)
{

}


