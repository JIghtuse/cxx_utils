#include <fstream>
#include <iostream>
#include <wc.h>

using namespace std;

// coreutils-like wc:
// print newline, word, and byte counts for each file
int main(int argc, char *argv[])
{
    if (argc == 1) {
        print_counts(cin, cout);
    } else {
        for (int i = 1; i < argc; ++i) {
            ifstream ifs{argv[i]};
            print_counts(ifs, cout);
            cout << " " << argv[i] << endl;
        }
    }

    return 0;
}
