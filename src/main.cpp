#include "headers.h"
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; ++i)
    {
        ifstream file(argv[i]);

        if (!file)
        {
            cerr << "Could not open the file.\n";
            return 1;
        }

        stringstream buffer;
        buffer << file.rdbuf();
        string input = buffer.str();

        simplifyString(input);

        Obj root = parse(input);

        cout << "\n S-Expression for " << argv[i] << " - \n\n";
        printSexp(root);
    }

    return 0;
}