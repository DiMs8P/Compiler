#include <iostream>
#include <string>
#include "DataReader/CharsReader.h"
#include "DataReader/FileReader.h"
#include "DataTable/PersistentTable.h"
#include "DataReader/StringsReader.h"
#include "DataTable/VolatileTable.h"
using namespace std;

int main(int argc, char* argv[])
{
    StringsReader reader1(R"(D:\RiderProjects\Compiler\Compiler\Compiler\InputData\razdelitelb.txt)");
    CharsReader reader2(R"(D:\RiderProjects\Compiler\Compiler\Compiler\InputData\razdelitelb.txt)");
    
    PersistentTable<char> Table;
    VolatileTable<string> Table2;
    Table.Load(reader2);
    
    if (Table.Find('}'))
    {
        cout << __FUNCTION__;
    }
    else
    {
        cout << "Not found";
    }

    Table2.Add("asd");
    _getchar_nolock();
    return 0;
}