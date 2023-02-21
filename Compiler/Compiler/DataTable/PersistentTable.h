#pragma once
#include <string>
#include "BaseDataTable.h"

template<class DataType>
class PersistentTable : public BaseDataTable<DataType>
{
public:
	virtual bool Find(const DataType& elem) override;
	virtual void Load(IDataReader<DataType>& reader) override;
};

template <class DataType>
bool PersistentTable<DataType>::Find(const DataType& elem)
{
    if (this->_data.find(elem) == this->_data.end())
    {
        return false;
    }
    return true;
}

template <class DataType>
void PersistentTable<DataType>::Load(IDataReader<DataType>& reader)
{
    this->_data.clear();
    for (const auto& value : reader.Read()) {

        // Insert each element
        // into the Set
        this->_data.insert(value);
    }
}
