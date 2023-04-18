#include "IndentificatorTable.h"

void IndentificatorTable::ChangeValue(int TableLine, int NewValue)
{
	_data[TableLine].value = NewValue;
}

void IndentificatorTable::ChangeType(int TableLine, int NewType)
{
	_data[TableLine].type = NewType;
}
