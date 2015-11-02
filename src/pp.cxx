#include <iostream>
#include <string>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

using namespace std;
namespace fs = boost::filesystem;
namespace po = boost::program_options;

void print_parts(const po::variables_map& vm)
{
    if (vm.count("extension")) {
        auto path = fs::path(vm["extension"].as<string>());
        cout << path.extension() << endl;
    }

    if (vm.count("filename")) {
        auto path = fs::path(vm["filename"].as<string>());
        cout << path.filename() << endl;
    }
}

/* path_parts: extract common parts from path */
int main(int argc, char *argv[])
{
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("extension", po::value<string>(), "print extension")
        ("filename", po::value<string>(), "print filename")
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

    print_parts(vm);
    return 0;
}
