#pragma once
#include <vector>

#include "../DataReader/IDataReader.h"

template<typename DataType>
class newPersistentTable
{
public:
    virtual int Find(const DataType& elem);
    //bool FindIf(const DataType& elem, std::function<bool(const DataType&)> lambda);
    virtual void Add(const DataType& elem);
    void Load(IDataReader<DataType>& reader);
    DataType GetElemByLine(const int LineNumber) const;
protected:
    std::vector<DataType> _data;
};

template <class DataType>
int newPersistentTable<DataType>::Find(const DataType& elem)
{
    for (int i = 0; i < _data.size(); i++)
    {
        if (elem == _data[i]) return i;
    }
    return - 1;
}

template <class DataType>
void newPersistentTable<DataType>::Add(const DataType& elem)
{
    _data.push_back(elem);
}

template <typename DataType>
void newPersistentTable<DataType>::Load(IDataReader<DataType>& reader)
{
    _data.clear();
    for (const auto& value : reader.Read()) {
        this->_data.push_back(value);
    }
}

template <typename DataType>
DataType newPersistentTable<DataType>::GetElemByLine(const int LineNumber) const
{
    return _data[LineNumber];
}