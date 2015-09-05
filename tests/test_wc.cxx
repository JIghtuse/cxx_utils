#include <wc.h>
#include <string>
#include <sstream>
#include <tuple>
#include <gtest/gtest.h>

using namespace std;

TEST(WcTest, EmptyPrintsZeros) {
    istringstream iss;

    size_t nlines, nwords, nbytes;
    tie(nlines, nwords, nbytes) = get_counts(iss);

    EXPECT_EQ(0, nlines);
    EXPECT_EQ(0, nwords);
    EXPECT_EQ(0, nbytes);
}

TEST(WcTest, OnelineOk) {
    istringstream iss{"a\n"};
    
    size_t nlines, nwords, nbytes;
    tie(nlines, nwords, nbytes) = get_counts(iss);

    EXPECT_EQ(1, nlines);
    EXPECT_EQ(1, nwords);
    EXPECT_EQ(2, nbytes);
}

TEST(WcTest, MulipleLinesOk) {
    istringstream iss{"cat\n  dog\n"};

    size_t nlines, nwords, nbytes;
    tie(nlines, nwords, nbytes) = get_counts(iss);

    EXPECT_EQ(2, nlines);
    EXPECT_EQ(2, nwords);
    EXPECT_EQ(10, nbytes);
}

TEST(WcTest, WithoutNewline) {
    istringstream iss{"a"};

    size_t nlines, nwords, nbytes;
    tie(nlines, nwords, nbytes) = get_counts(iss);

    EXPECT_EQ(0, nlines);
    EXPECT_EQ(1, nwords);
    EXPECT_EQ(1, nbytes);
}