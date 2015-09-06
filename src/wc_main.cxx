#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include <tuple>
#include <wc.h>

using namespace std;

// coreutils-like wc:
// print newline, word, and byte counts for each file
int main(int argc, char *argv[])
{
    if (argc == 1) {
        print_counts(cin, cout);
    } else {
        vector<size_t> nlines, nwords, nbytes;
        for (int i = 1; i < argc; ++i) {
            ifstream ifs{argv[i]};
            size_t nl, nw, nb;
            tie(nl, nw, nb) = get_counts(ifs);
            nlines.push_back(nl);
            nwords.push_back(nw);
            nbytes.push_back(nb);
        }
        auto nl_total{accumulate(nlines.begin(), nlines.end(), 0)};
        auto nw_total{accumulate(nwords.begin(), nwords.end(), 0)};
        auto nb_total{accumulate(nbytes.begin(), nbytes.end(), 0)};

        size_t nl_width = 1 + round(0.5 + log10(nl_total));
        size_t nw_width = 1 + round(0.5 + log10(nw_total));
        size_t nb_width = 1 + round(0.5 + log10(nb_total));

        for (int i = 1; i < argc; ++i) {
            cout << setw(nl_width) << nlines[i - 1]
                 << setw(nw_width) << nwords[i - 1]
                 << setw(nb_width) << nbytes[i - 1]
                 << " " << argv[i] << endl;
        }
        cout << setw(nl_width) << nl_total
             << setw(nw_width) << nw_total
             << setw(nb_width) << nb_total
             << " total" << endl;
    }

    return 0;
}
