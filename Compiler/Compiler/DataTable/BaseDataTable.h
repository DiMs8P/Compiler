#pragma once
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "../DataReader/IDataReader.h"

template<typename DataType>
class BaseDataTable
{
public:
    virtual ~BaseDataTable() = default;
    BaseDataTable() = default;

    virtual void Load(IDataReader<DataType>& reader) = 0;
    virtual bool Find(const DataType& Elem) = 0;
protected:
    std::unordered_multiset<DataType> _data;
};