#pragma once
#include "Token.h"
#include <string>


#include "Constant.h"
#include "Identificator.h"
#include "DataTable/PersistentTable.h"
#include "DataTable/VolatileTable.h"

struct Token;
using namespace std;
namespace std
{
	template <> struct hash<Token>
	{
		std::size_t operator()(Token const& token) const noexcept
		{
			const size_t numHash = std::hash<int>()(token.TableNumber);
			const size_t lineHash = std::hash<int>()(token.LineNumber) << 1;
			return numHash ^ lineHash;
		}
	};

	template <> struct hash<Constant>
	{
		std::size_t operator()(Token const& token) const noexcept
		{
			const size_t numHash = std::hash<int>()(token.TableNumber);
			const size_t lineHash = std::hash<int>()(token.LineNumber) << 1;
			return numHash ^ lineHash;
		}
	};
}

class LexicalAnalyzer
{
public:
	friend class Compiler;

	LexicalAnalyzer();
	void Analyze(const vector<char>& program);

protected:
	vector<PersistentTable<string>> StringTables;
	VolatileTable <string> ConstantTable;
	VolatileTable <Token> TokenTable;
	VolatileTable <string> IdTable;
};

