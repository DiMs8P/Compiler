#include "CharsReader.h"

void CharsReader::Read(unordered_set<char>& outputData)
{
    ReadChars(outputData);
}

void CharsReader::ReadChars(unordered_set<char>& outputData) const
{
    ifstream fin(_filePath);
    if (!fin.is_open())
    {
        throw exception("Invalid file path!");
    }
    
    char symbol;
    while (fin >> symbol)
    {
        outputData.insert(symbol);
    }
    fin.close();
}
