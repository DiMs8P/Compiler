#pragma once
#include "BaseDataTable.h"

template<class DataType>
class VolatileTable : public BaseDataTable<DataType>
{
public:
    virtual bool Find(const DataType& elem) override;
    virtual void Load(IDataReader<DataType>& reader) override;
    virtual void Add(const DataType& elem);
};

template <class DataType>
bool VolatileTable<DataType>::Find(const DataType& elem)
{
    if (this->_data.find(elem) == this->_data.end())
    {
        Add(elem);
        return false;
    }
    return true;
}

template <class DataType>
void VolatileTable<DataType>::Add(const DataType& elem)
{
    this->_data.insert(elem);
}

template <class DataType>
void VolatileTable<DataType>::Load(IDataReader<DataType>& reader)
{
    for (const auto& value : reader.Read()) {

        // Insert each element
        // into the Set
        this->_data.insert(value);
    }
}