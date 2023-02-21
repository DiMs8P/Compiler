
#include "Compiler.h"

#include "DataTable/VolatileTable.h"
using namespace std;

class OneToken
{
public:
	int TableLine;
};

int main(int argc, char* argv[])
{
	Compiler compiler(R"(InputData\inputprog.txt)");
	VolatileTable<OneToken> table;
	OneToken tokenToFind{};
	tokenToFind.TableLine = 1;

	//table.FindIf(tokenToFind, [tokenToFind](const OneToken& tokenToSearch) {return tokenToFind.TableLine == tokenToSearch.TableLine; });

    return 0;
}
