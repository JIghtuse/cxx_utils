#include <wc.h>

#include <cctype>
#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

tuple<size_t, size_t, size_t> get_counts(std::istream& in)
{
    size_t nlines{0};
    size_t nwords{0};
    size_t nbytes{0};

    bool inside_word{false};
    char c;

    while (in.read(&c, 1)) {
        ++nbytes;

        if (c == '\n')
            ++nlines;

        if (isspace(c)) {
            if (inside_word)
                ++nwords;
            inside_word = false;
        } else {
            inside_word = true;
        }
    }
    if (inside_word)
        ++nwords;
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
