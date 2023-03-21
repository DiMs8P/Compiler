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
	string buffer;
	for (int i = 0; i < program.size(); i++) {
		if (isdigit(program[i]))
		{
			while (isdigit(program[i]))
			{
				buffer.push_back(program[i]);
				i++;
			}
			ConstantTable.Find(buffer);
			TokenTable.Add({ 4,ConstantTable.Find(buffer) });
			buffer.clear();
		}
		if (isupper(program[i]))
		{
			while (isdigit(program[i]) || isupper(program[i]) || islower(program[i]))
			{
				buffer.push_back(program[i]);
				i++;
			}
			IdTable.Find(buffer);
			TokenTable.Add({ 5,IdTable.Find(buffer) });
			buffer.clear();
		}
		if (islower(program[i]))
		{
			while (islower(program[i]))
			{
				buffer.push_back(program[i]);
				i++;
			}
			if (program[i] == ' ' || program[i] == '(')
			{
				if (StringTables[0].Find(buffer) != -1)
					TokenTable.Add({ 1,StringTables[0].Find(buffer) });
				else
				{
					IdTable.Find(buffer);
					TokenTable.Add({ 5, IdTable.Find(buffer) });
				}

			}
			else
			{
				while (isupper(program[i]) || isdigit(program[i]) || islower(program[i]))
				{
					buffer.push_back(program[i]);
					i++;
				}
				IdTable.Find(buffer);
				TokenTable.Add({ 5, IdTable.Find(buffer) });
			}
			buffer.clear();
		}
		if (program[i] != ' ')
		{
			buffer.push_back(program[i]);
			if (StringTables[1].Find(buffer) != -1)
				TokenTable.Add({ 2, StringTables[1].Find(buffer) });
			if (program[i] == '|')
			{
				if (i + 1 < program.size() && program[i + 1] == '|')
				{
					i++;
					buffer.push_back(program[i]);
					TokenTable.Add({ 3, StringTables[2].Find(buffer) });
				}
				else
				{
					//ошибка;
				}
			}
			buffer.clear();
		}
	}

}


