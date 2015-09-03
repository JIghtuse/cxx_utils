#include <iostream>
#include <wc.h>

using namespace std;

// coreutils-like wc:
// print newline, word, and byte counts for each file
int main(int argc, char *argv[])
{
    if (argc == 1) {
        print_counts(std::cin, std::cout);
    } else {
        for (int i = 0; i < argc; ++i) {
            print_counts(std::cin, std::cout);
            std::cout << " " << argv[i] << std::endl;
        }
    }

    return 0;
}
