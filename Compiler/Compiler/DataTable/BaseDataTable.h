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

    virtual void Load(IDataReader<DataType>& reader)
    {
        reader.Read(_data);
    }
    virtual bool Find(DataType Elem);
protected:
    std::unordered_set<DataType> _data;
};

template <typename DataType>
bool BaseDataTable<DataType>::Find(DataType Elem)
{
    if (_data.find(Elem) == _data.end())
    {
        return false;
    }
    return true;
}