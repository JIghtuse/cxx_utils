#include <wc.h>

#include <sstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void print_counts(istream& in, ostream& out)
{
    size_t nlines{0};
    size_t nwords{0};
    size_t nbytes{0};

    for (string s; getline(in, s);) {
        ++nlines;

        istringstream iss(s);
        for (string word; iss >> word;)
            ++nwords;

        nbytes += s.size() + 1; // all characters + newline
    }

    out << nlines << " " << nwords << " " << nbytes;
}
