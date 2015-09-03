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

TEST(WcTest, OnelineOk) {
    istringstream iss{"a\n"};
    ostringstream oss;

    print_counts(iss, oss);

    istringstream actual(oss.str());
    size_t nlines;
    size_t nwords;
    size_t nbytes;
    actual >> nlines >> nwords >> nbytes;

    EXPECT_EQ(1, nlines);
    EXPECT_EQ(1, nwords);
    EXPECT_EQ(2, nbytes);
}

TEST(WcTest, MulipleLinesOk) {
    istringstream iss{"cat\n  dog\n"};
    ostringstream oss;

    print_counts(iss, oss);

    istringstream actual(oss.str());
    size_t nlines;
    size_t nwords;
    size_t nbytes;
    actual >> nlines >> nwords >> nbytes;

    EXPECT_EQ(2, nlines);
    EXPECT_EQ(2, nwords);
    EXPECT_EQ(10, nbytes);
}
