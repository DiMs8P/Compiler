#pragma once
#include "FileReader.h"

class CharsReader : public FileReader<char>
{
public:
    CharsReader(const string& filePath) : FileReader(filePath){}
    vector<char> Read() override;

protected:
    vector<char> ReadChars() const;
};
