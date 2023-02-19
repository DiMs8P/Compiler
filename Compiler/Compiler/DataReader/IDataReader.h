#pragma once
#include <string>
#include <unordered_set>
#include <vector>

template<typename DataType>
class IDataReader
{
public:
    virtual std::vector<DataType> Read() = 0;
};
