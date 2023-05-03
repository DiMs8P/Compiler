#include "LexicalAnalyzer.h"
#include "ExceptionManager/ExceptionManager.h"
#include "Identificator.h"
#include "DataReader/StringsReader.h"
#include "IndentificatorTable.h"

LexicalAnalyzer::LexicalAnalyzer()
{
	StringsReader readerString(R"(InputData\word.txt)");
	newPersistentTable<string> StringTable;
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
	std::ofstream errorStream;
	errorStream.open("errors.txt");
	ExceptionManager Error(errorStream);

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
			i--;
			fout << "(4, " << ConstantTable.Find({stoi(buffer), 0}) << " ) ";
			TokenTable.Add({ 4,ConstantTable.Find({stoi(buffer)}) });
			buffer.clear();
		}
		else if (isupper(program[i]))
		{
			while (isdigit(program[i]) || isupper(program[i]) || islower(program[i]))
			{
				buffer.push_back(program[i]);
				i++;
			}
			i--;
			fout << "(5, " << IdTable.Find({buffer}) << " ) ";
			TokenTable.Add({ 5,IdTable.Find({buffer}) });
			buffer.clear();
		}
		else if (islower(program[i]))
		{
			while (islower(program[i]))
			{
				buffer.push_back(program[i]);
				i++;
			}
			if (program[i] == ' ' || program[i] == '(')
			{

				if (StringTables[0].Find(buffer) != -1)
				{
					fout << "(1, " << StringTables[0].Find(buffer) << " ) ";
					TokenTable.Add({ 1,StringTables[0].Find(buffer) });
				}
				else
				{
					fout << "(5, " << IdTable.Find({buffer}) << " ) ";
					TokenTable.Add({ 5, IdTable.Find({buffer}) });
				}

				//if (program[i] == '(')
				//{
				//	fout << "(2, " << StringTables[1].Find("(") << " ) ";
				//}
				i--;
			}
			else
			{
				while (isupper(program[i]) || isdigit(program[i]) || islower(program[i]))
				{
					buffer.push_back(program[i]);
					i++;
				}
				i--;
				fout << "(5, " << IdTable.Find({buffer}) << " ) ";
				TokenTable.Add({ 5, IdTable.Find({buffer}) });
			}

			buffer.clear();
		}
		else if (program[i] != ' ' && program[i] != '\n' && program[i] != '\t')
		{
			buffer.push_back(program[i]);
			if (StringTables[1].Find(buffer) != -1)
			{
				fout << "(2, " << StringTables[1].Find(buffer) << " ) ";
				TokenTable.Add({ 2, StringTables[1].Find(buffer) });
			}
			else if (program[i] == '|')
			{
				if (i + 1 < program.size() && program[i + 1] == '|')
				{
					i++;
					buffer.push_back(program[i]);
					fout << "(3, " << StringTables[2].Find(buffer) << " ) ";
					TokenTable.Add({ 3, StringTables[2].Find(buffer) });
				}
				else
				{
					Error.Exception("Wrong symbol");
				}

			}
			else if (program[i] == '&')
			{
				if (i + 1 < program.size() && program[i + 1] == '&')
				{
					i++;
					buffer.push_back(program[i]);
					fout << "(3, " << StringTables[2].Find(buffer) << " ) ";
					TokenTable.Add({ 3, StringTables[2].Find(buffer) });
				}
				else
				{
					Error.Exception("Wrong symbol");
				}
			}
			else if (program[i] == '+')
			{
				if (i + 1 < program.size() && program[i + 1] == '+')
				{
					i++;
					buffer.push_back(program[i]);
					fout << "(3, " << StringTables[2].Find(buffer) << " ) ";
					TokenTable.Add({ 3, StringTables[2].Find(buffer) });
				}
				else
				{
					if (StringTables[2].Find(buffer) != -1)
					{
						fout << "(3, " << StringTables[2].Find(buffer) << " ) ";
						TokenTable.Add({ 3, StringTables[2].Find(buffer) });
					}
					else {
						Error.Exception("Wrong symbol");
					}
				}

			}

			else if (program[i] == '-')
			{
				if (i + 1 < program.size() && program[i + 1] == '-')
				{
					i++;
					buffer.push_back(program[i]);
					fout << "(3, " << StringTables[2].Find(buffer) << " ) ";
					TokenTable.Add({ 3, StringTables[2].Find(buffer) });
				}
				else
				{
					if (StringTables[2].Find(buffer) != -1)
					{
						fout << "(3, " << StringTables[2].Find(buffer) << " ) ";
						TokenTable.Add({ 3, StringTables[2].Find(buffer) });
					}
					else {
						Error.Exception("Wrong symbol");
					}
				}
			}
			else if (program[i] == '/')
			{
				if (i + 1 < program.size() && program[i + 1] == '/')
				{
					i++;

					while (i < program.size() && program[i] != '\n')
					{
						i++;
					}
				}
				else if (i + 1 < program.size() && program[i + 1] == '*')
				{
					i = i + 2;
					while (i + 1 < program.size() && program[i] != '*' && program[i + 1] != '/')
					{
						i++;
					}
					i++;
				}
				else
				{
					Error.Exception("Wrong symbol");
				}
			}
			else
			{
				if (i + 1 < program.size() && program[i + 1] == '=')
				{
					i++;
					buffer.push_back(program[i]);
					fout << "(3, " << StringTables[2].Find(buffer) << " ) ";
					TokenTable.Add({ 3, StringTables[2].Find(buffer) });
				}
				else
				{
					if (StringTables[2].Find(buffer) != -1)
					{
						fout << "(3, " << StringTables[2].Find(buffer) << " ) ";
						TokenTable.Add({ 3, StringTables[2].Find(buffer) });
					}
					else
					{
						Error.Exception("Wrong symbol");
					}
				}
			}
			buffer.clear();
		}
		else if (program[i] == '\n')
		{
			fout << endl;
		}
		else if (program[i] != ' ' && program[i] != '\t')
		{
			Error.Exception("Wrong symbol");
		}
	}
}


