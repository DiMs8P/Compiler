#pragma once
#include "Identificator.h"
#include "DataTable/newVolatileTable.h"

namespace std
{
	template <> struct hash<Identificator>
	{
		std::size_t operator()(Identificator const& token) const noexcept
		{
			const size_t numHash = std::hash<int>()(token.type);
			const size_t lineHash = std::hash<int>()(token.value) << 1;
			const size_t lineLength = std::hash<string>()(token.name);
			return numHash ^ lineHash ^ lineLength;
		}
	};
}

class IndentificatorTable : public newVolatileTable<Identificator>
{
public:
	void ChangeValue(int TableLine, int NewValue);
	void ChangeType(int TableLine, int NewType);
};

