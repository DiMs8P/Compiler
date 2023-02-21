#include "CharsReader.h"

vector<char> CharsReader::Read()
{
	return ReadChars();
}

vector<char> CharsReader::ReadChars() const
{
	ifstream fin(_filePath);
	if (!fin.is_open())
	{
		throw exception("Invalid file path!");
	}

	vector<char> output;
	char symbol;
	while (fin >> noskipws >> symbol)
	{
		output.push_back(symbol);
	}
	fin.close();

	return output;
}
