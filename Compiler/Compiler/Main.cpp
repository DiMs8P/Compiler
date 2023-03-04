#include "Compiler.h"
#include "IndentificatorTable.h"
#include "DataReader/CharsReader.h"
#include "DataReader/StringsReader.h"

using namespace std;

int main(int argc, char* argv[])
{
	/*	Compiler compiler(R"(InputData\inputprog.txt)");
		compiler.Compile()*/;

		StringsReader reader((R"(InputData\znak.txt)"));

		PersistentTable<string> table;
		table.Load(reader);
		table.ShowData();

		auto distance = table.Find("&&");

		IndentificatorTable StringTable1;
		StringTable1.Add({ "asd",1,1 });
		StringTable1.Add({ "asd121",1,1 });
		auto elem = StringTable1.GetElemByLine(1);
		cout << "elem type: " << elem.type << " elem Value : " << elem.value << endl;
		StringTable1.ChangeType(1, 10);
		StringTable1.ChangeValue(1, 11);

		elem = StringTable1.GetElemByLine(1);

		elem = StringTable1.GetElemByLine(1);
		cout << "elem type: " << elem.type << " elem Value : " << elem.value << endl;
		StringTable1.Add({ "asd",1,1 });
		return 0;
}
