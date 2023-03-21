#include "LexicalAnalyzer.h"
#include "ExceptionManager/ExceptionManager.h"
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
	ExceptionManager Error;
	string buffer;
	ofstream fout("Tokens.txt");
	for (int i = 0; i < program.size(); i++) {
		if (isdigit(program[i]))
		{
			while (isdigit(program[i]))
			{
				buffer.push_back(program[i]);
				i++;
			}
			ConstantTable.Find(buffer);
			fout << "(4, " << ConstantTable.Find(buffer) << " ) ";
			/*TokenTable.Add({ 4,ConstantTable.Find(buffer) });
			*/buffer.clear();
		}
		if (isupper(program[i]))
		{
			while (isdigit(program[i]) || isupper(program[i]) || islower(program[i]))
			{
				buffer.push_back(program[i]);
				i++;
			}
			IdTable.Find(buffer);
			fout << "(5, " << IdTable.Find(buffer) << " ) ";
			//TokenTable.Add({ 5,IdTable.Find(buffer) });
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
					fout << "(1, " << StringTables[0].Find(buffer) << " ) ";
				//TokenTable.Add({ 1,StringTables[0].Find(buffer) });
				else
				{
					IdTable.Find(buffer);
					fout << "(5, " << IdTable.Find(buffer) << " ) ";
					//TokenTable.Add({ 5, IdTable.Find(buffer) });
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
				fout << "(5, " << IdTable.Find(buffer) << " ) ";
				//TokenTable.Add({ 5, IdTable.Find(buffer) });
			}
			buffer.clear();
		}
		if (program[i] != ' ' && program[i] != '\n' && program[i] != '\t')
		{
			buffer.push_back(program[i]);
			if (StringTables[1].Find(buffer) != -1)
				fout << "(2, " << StringTables[1].Find(buffer) << " ) ";
			//TokenTable.Add({ 2, StringTables[1].Find(buffer) });
			if (program[i] == '|')
			{
				if (i + 1 < program.size() && program[i + 1] == '|')
				{
					i++;
					buffer.push_back(program[i]);
					fout << "(3, " << StringTables[2].Find(buffer) << " ) ";
					//TokenTable.Add({ 3, StringTables[2].Find(buffer) });
				}
				else
				{
					Error.Exception("Ошибка какая-то");
				}

			}
			if (program[i] == '&')
			{
				if (i + 1 < program.size() && program[i + 1] == '&')
				{
					i++;
					buffer.push_back(program[i]);
					fout << "(3, " << StringTables[2].Find(buffer) << " ) ";
					//TokenTable.Add({ 3, StringTables[2].Find(buffer) });
				}
				else
				{
					Error.Exception("Ошибка какая-то");
				}
			}
			else
			{
				if (i + 1 < program.size() && program[i + 1] == '=')
				{
					i++;
					buffer.push_back(program[i]);
					fout << "(3, " << StringTables[2].Find(buffer) << " ) ";
					//TokenTable.Add({ 3, StringTables[2].Find(buffer) });
				}
				else
				{
					fout << "(3, " << StringTables[2].Find(buffer) << " ) ";
					//TokenTable.Add({ 3, StringTables[2].Find(buffer) });
				}
			}
			buffer.clear();
		}
		if (program[i] == '\n')
		{
			fout << endl;
		}
	}
	int x = 2;
}


