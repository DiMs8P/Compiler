#pragma once
#include "FileReader.h"

class CharsReader : public FileReader<char>
{
public:
    CharsReader(const string& filePath) : FileReader(filePath){}
    void Read(unordered_set<char>& outputData) override;

protected:
    void ReadChars(unordered_set<char>& outputData) const;
};
