#include <wc.h>

#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

tuple<size_t, size_t, size_t> get_counts(std::istream& in)
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
    return make_tuple(nlines, nwords, nbytes);
}

void print_counts(istream& in, ostream& out)
{
    size_t nlines;
    size_t nwords;
    size_t nbytes;
    
    tie(nlines, nwords, nbytes) = get_counts(in);

    out << nlines << " " << nwords << " " << nbytes;
}
