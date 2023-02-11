#include "StringsReader.h"

void StringsReader::Read(unordered_set<string>& outputData)
{
    ReadStrings(outputData);
}

void StringsReader::ReadStrings(unordered_set<string>& outputData) const
{
    ifstream fin(_filePath);
    if (!fin.is_open())
    {
        throw exception("Invalid file path!");
    }

    string str;
    while (getline(fin, str))
    {
        outputData.insert(str);
    }
    fin.close();
}
