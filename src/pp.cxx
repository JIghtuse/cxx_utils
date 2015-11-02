#include <iostream>
#include <string>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

using namespace std;
namespace fs = boost::filesystem;
namespace po = boost::program_options;

/* path_parts: extract common parts from path */
int main(int argc, char *argv[])
{
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("ext", po::value<string>(), "print extension")
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.size() == 0) {
        cout << desc << endl;
        return 1;
    }
    if (vm.count("help")) {
        cout << desc << endl;
        return 0;
    }

    if (vm.count("ext")) {
        auto path = fs::path(vm["ext"].as<string>());
        cout << path.extension() << endl;
    }

    return 0;
}
