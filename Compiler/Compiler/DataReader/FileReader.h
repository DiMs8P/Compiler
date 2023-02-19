#pragma once
#include "IDataReader.h"
#include <fstream>

using namespace std;

template<typename DataType>
class FileReader : public IDataReader<DataType>
{
public:
    explicit FileReader(const string& filePath);
    void SetFilePath(const string& filePath);
    virtual vector<DataType> Read() = 0;

protected:
    string _filePath;
};

template <typename DataType>
FileReader<DataType>::FileReader(const string& filePath)
{
    SetFilePath(filePath);
}

template<typename DataType>
inline void FileReader<DataType>::SetFilePath(const string& filePath)
{
    _filePath = filePath;
}
