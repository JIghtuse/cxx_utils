#include <algorithm>
#include <experimental/optional>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <set>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

using std::experimental::nullopt;
using std::experimental::optional;

using Link = std::string;
using Links = std::set<Link>;

const std::string kHTTPPrefix{"http://"};

optional<Links> get_links(const std::string& fname, const std::string& hostname)
{
    auto in{std::ifstream{fname}};
    if (!in) {
        return nullopt;
    }

    std::regex re_link{R"#(href\s*=\s*['"]([^'"]*)")#", std::regex_constants::icase};

    auto links{Links{}};
    for (std::string line; std::getline(in, line);) {
        auto begin = std::sregex_iterator(line.begin(), line.end(), re_link);

        for (auto it = begin; it != std::sregex_iterator{}; ++it) {
            std::smatch match = *it;
            auto link = std::string{match[1]};
            if (!std::equal(kHTTPPrefix.begin(), kHTTPPrefix.end(), link.begin())) {
                link = kHTTPPrefix + hostname + link;
            }
            links.insert(link);
        }
    }
    return links;
}

// Reads html file and tries to extract all unique links from it
int main(int argc, char *argv[])
{
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("input-file", po::value<std::string>(), "HTML file to parse")
        ("hostname", po::value<std::string>(), "hostname to append to urls without it")
        ("image", "print image urls")
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.size() == 0) {
        std::cout << desc << std::endl;
        return 1;
    }
    if (!vm.count("input-file") || vm.count("help")) {
        std::cout << desc << std::endl;
        return 0;
    }

    const auto input_file{vm["input-file"].as<std::string>()};
    const auto hostname = vm.count("hostname") ? vm["hostname"].as<std::string>() : "";

    auto links = get_links(input_file, hostname);

    if (links) {
        for (const auto& link : *links) {
            std::cout << link << std::endl;
        }
    } else {
        std::cerr << "Cannot open file " << input_file << std::endl;
    }
}
