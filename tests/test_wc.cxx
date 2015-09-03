#include <wc.h>
#include <string>
#include <sstream>
#include <gtest/gtest.h>

using namespace std;

TEST(WcTest, EmptyPrintsZeros) {
    istringstream iss;
    ostringstream oss;

    print_counts(iss, oss);

    istringstream actual(oss.str());
    size_t nlines;
    size_t nwords;
    size_t nbytes;
    actual >> nlines >> nwords >> nbytes;

    EXPECT_EQ(0, nlines);
    EXPECT_EQ(0, nwords);
    EXPECT_EQ(0, nbytes);
}
