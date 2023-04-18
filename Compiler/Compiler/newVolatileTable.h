#pragma once
#include <vector>
#include <iostream>

using namespace std;
template<typename DataType>
class newVolatileTable
{
public:
	virtual int Find(const DataType& elem);
	//bool FindIf(const DataType& elem, std::function<bool(const DataType&)> lambda);
	virtual void Add(const DataType& elem);
	DataType GetElemByLine(const int LineNumber) const;
private:

	vector<DataType> _data;
};

template <class DataType>
int newVolatileTable<DataType>::Find(const DataType& elem)
{
	for (int i = 0; i < _data.size(); i++)
	{
		if (elem == _data[i])
			return i;
	}
	Add(elem);
	return i;

	//auto It = this->_data.find(elem);
	//if (It == this->_data.end())
	//{
	//	Add(elem);
	//	return std::distance(this->_data.begin(), It);
	//}
	//return std::distance(this->_data.begin(), It);
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
DataType newVolatileTable<DataType>::GetElemByLine(const int LineNumber) const
{
	return _data[LineNumber];
}

