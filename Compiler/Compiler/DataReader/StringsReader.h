#pragma once
#include "FileReader.h"

class StringsReader : public FileReader<string>
{
public:
    StringsReader(const string& filePath) : FileReader(filePath){}
    void Read(unordered_set<string>& outputData) override;

protected:
    void ReadStrings(unordered_set<string>& outputData) const;
};
