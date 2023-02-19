#include "StringsReader.h"

vector<string> StringsReader::Read()
{
    return ReadStrings();
}

vector<string> StringsReader::ReadStrings() const
{
    ifstream fin(_filePath);
    if (!fin.is_open())
    {
        throw exception("Invalid file path!");
    }

    vector<string> output;
    string str;
    while (getline(fin, str))
    {
        output.push_back(str);
    }
    fin.close();

    return output;
}
