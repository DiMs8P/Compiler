#pragma once
#include "FileReader.h"

class StringsReader : public FileReader<string>
{
public:
    StringsReader(const string& filePath) : FileReader(filePath){}
    vector<string> Read() override;

protected:
    vector<string> ReadStrings() const;
};
