#pragma once
#include "BaseDataTable.h"

template<class DataType>
class VolatileTable : public BaseDataTable<DataType>
{
public:
    bool Find(DataType elem) override;
    virtual void Add(DataType elem);
};

template <class DataType>
bool VolatileTable<DataType>::Find(DataType elem)
{
    if (!BaseDataTable<DataType>::Find(elem))
    {
        Add(elem);
        return false;
    }
    return true;
}

template <class DataType>
void VolatileTable<DataType>::Add(DataType elem)
{
    this->_data.insert(elem);
}

