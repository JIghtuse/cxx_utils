#include <wc.h>

#include <string>
#include <vector>

using namespace std;

void print_counts(const istream&, ostream& out)
{
    size_t nlines{0};
    size_t nwords{0};
    size_t nbytes{0};

    out << nlines << " " << nwords << " " << nbytes;
}
