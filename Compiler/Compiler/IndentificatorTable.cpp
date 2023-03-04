#include "IndentificatorTable.h"

void IndentificatorTable::ChangeValue(int TableLine, int NewValue)
{
	auto It = this->_data.begin();
	std::advance(It, TableLine);
	auto NewItem = *It;
	this->_data.erase(It);

	NewItem.value = NewValue;
	this->_data.insert(NewItem);

}

void IndentificatorTable::ChangeType(int TableLine, int NewType)
{
	auto It = this->_data.begin();
	std::advance(It, TableLine);
	auto NewItem = *It;
	this->_data.erase(It);

	NewItem.type = NewType;
	this->_data.insert(NewItem);
}
