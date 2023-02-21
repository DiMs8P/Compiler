#pragma once
#include <unordered_set>
#include "../DataReader/IDataReader.h"

template<typename DataType>
class BaseDataTable
{
public:
    virtual void Load(IDataReader<DataType>& reader) = 0;
    virtual bool Find(const DataType& Elem) = 0;
protected:
    std::unordered_multiset<DataType> _data;
};