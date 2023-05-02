#pragma once
#include<vector>

#include "../DataReader/IDataReader.h"

template<typename DataType>
class newVolatileTable
{
public:
	virtual int Find(const DataType& elem);
	int Size() const;
	//bool FindIf(const DataType& elem, std::function<bool(const DataType&)> lambda);
	virtual void Add(const DataType& elem);
	void Load(IDataReader<DataType>& reader);
	DataType GetElemByLine(const int LineNumber) const;
protected:
	std::vector<DataType> _data;
};

template <class DataType>
int newVolatileTable<DataType>::Find(const DataType& elem)
{
	for (int i = 0; i < _data.size(); i++)
	{
		if (elem == _data[i]) return i;
	}
	Add(elem);
	return _data.size() - 1;
}

template <typename DataType>
int newVolatileTable<DataType>::Size() const
{
	return _data.size();
}

//template <class DataType>
//bool newVolatileTable<DataType>::FindIf(const DataType& elem, std::function<bool(const DataType&)> lambda)
//{
//	if (find_if(this->_data.begin(), this->_data.end(), lambda) == this->_data.end())
//	{
//		Add(elem);
//		return false;
//	}
//	return true;
//}

template <class DataType>
void newVolatileTable<DataType>::Add(const DataType& elem)
{
	_data.push_back(elem);
}

template <typename DataType>
void newVolatileTable<DataType>::Load(IDataReader<DataType>& reader)
{
	_data.clear();
	for (const auto& value : reader.Read()) {
		this->_data.push_back(value);
	}
}

template <typename DataType>
DataType newVolatileTable<DataType>::GetElemByLine(const int LineNumber) const
{
	return _data[LineNumber];
}

