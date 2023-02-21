#include "Compiler.h"
#include "DataReader/CharsReader.h"

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
}

Compiler::Compiler(const string& inputFilePath)
{
	CharsReader reader(inputFilePath);
	program = reader.Read();
}

void Compiler::Compile()
{
	lexicalAnalyzer.Analyze(program);
}
