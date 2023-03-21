#include "LexicalAnalyzer.h"

#include "Identificator.h"
#include "DataReader/StringsReader.h"
#include "IndentificatorTable.h"

LexicalAnalyzer::LexicalAnalyzer()
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

void LexicalAnalyzer::Analyze(const vector<char>& program)
{

}


