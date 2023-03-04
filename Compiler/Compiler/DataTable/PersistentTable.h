#pragma once
#include <iostream>
#include <string>
#include "BaseDataTable.h"

template<class DataType>
class PersistentTable : public BaseDataTable<DataType>
{
public:
	virtual int Find(const DataType& elem) override;
	virtual void Load(IDataReader<DataType>& reader) override;

	void ShowData();
};

template <class DataType>
int PersistentTable<DataType>::Find(const DataType& elem)
{
	auto It = this->_data.find(elem);
	if (It == this->_data.end())
	{
		return -1;
	}
	return std::distance(this->_data.begin(), It);
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

template <class DataType>
void PersistentTable<DataType>::ShowData()
{
	for (auto itr = this->_data.begin();
		itr != this->_data.end(); itr++)
	{
		std::cout << *itr << std::endl;
	}
}
