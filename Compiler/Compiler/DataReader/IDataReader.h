#pragma once
#include <string>
#include <unordered_set>
#include <vector>

template<typename DataType>
class IDataReader
{
public:
    virtual void Read(std::unordered_set<DataType>& outputData) = 0;
};
