#include <iostream>
#include <fstream>
#include <optional>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/error_of.hpp>
#include <boost/accumulators/statistics/error_of_mean.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/moment.hpp>
#include <boost/accumulators/statistics/stats.hpp>

namespace acc = boost::accumulators;

using Stats = acc::stats<
    acc::tag::mean,
    acc::tag::moment<2>,
    acc::features<acc::tag::count>,
    acc::tag::error_of<acc::tag::mean>>;
using Accumulator = acc::accumulator_set<double, Stats>;

std::optional<Accumulator> gatherStats(const char* filename)
{
    std::ifstream in{filename};
    if (!in) {
        return std::nullopt;
    }

    auto accumulator = Accumulator{};
    for (double d; in >> d;) {
        accumulator(d);
    }

    return accumulator;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "usage: " << argv[0] << " <filename>" << '\n';
        return 1;
    }

    auto accumulator = gatherStats(argv[1]);
    if (accumulator) {
        std::cout << "Count:         " << acc::count(*accumulator) << '\n';
        std::cout << "Mean:          " << acc::mean(*accumulator) << '\n';
        std::cout << "Moment:        " << acc::moment<2>(*accumulator) << '\n';
        std::cout << "Error of mean: " << acc::error_of<acc::tag::mean>(*accumulator) << '\n';
    } else {
        std::cerr << "Failed to get statistics for file '" << argv[1] << "'\n";
        return 1;
    }
}
