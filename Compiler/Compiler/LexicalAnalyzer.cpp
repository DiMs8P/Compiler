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

	IndentificatorTable StringTable1;
	StringTable1.Add({ "asd",1,1 });
	StringTable1.Add({ "asd",1,1 });
	StringTable1.ChangeType(1, 10);
	StringTable1.ChangeValue(1, 11);
	StringTable1.Add({ "asd",1,1 });
}

void LexicalAnalyzer::Analyze(const vector<char>& program)
{

}


