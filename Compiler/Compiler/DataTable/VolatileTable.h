#pragma once
#include "BaseDataTable.h"
#include <functional>

template<typename DataType>
class VolatileTable : public BaseDataTable<DataType>
{
public:
	virtual int Find(const DataType& elem) override;
	bool FindIf(const DataType& elem, std::function<bool(const DataType&)> lambda);
	virtual void Load(IDataReader<DataType>& reader) override;
	virtual void Add(const DataType& elem);
	DataType GetElemByLine(const int LineNumber) const;
};

template <class DataType>
int VolatileTable<DataType>::Find(const DataType& elem)
{
	auto It = this->_data.find(elem);
	if (It == this->_data.end())
	{
		Add(elem);
		return std::distance(this->_data.begin(), It);
	}
	return std::distance(this->_data.begin(), It);
}

template <class DataType>
bool VolatileTable<DataType>::FindIf(const DataType& elem, std::function<bool(const DataType&)> lambda)
{
	if (find_if(this->_data.begin(), this->_data.end(), lambda) == this->_data.end())
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

template <typename DataType>
DataType VolatileTable<DataType>::GetElemByLine(const int LineNumber) const
{
	auto It = this->_data.begin();
	std::advance(It, LineNumber);
	return *It;
}

template <class DataType>
void VolatileTable<DataType>::Load(IDataReader<DataType>& reader)
{
	this->_data.clear();
	for (const auto& value : reader.Read()) {
		this->_data.insert(value);
	}
}
