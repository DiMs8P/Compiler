#include "Compiler.h"

using namespace std;

int main(int argc, char* argv[])
{
	Compiler compiler(R"(InputData\inputprog.txt)");
	compiler.Compile();

    return 0;
}
