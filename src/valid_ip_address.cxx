#include <iomanip>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/program_options.hpp>

namespace asio = boost::asio;
namespace po = boost::program_options;

namespace {

const char* kAddressArgument = "address";

} // namespace

int main(int argc, char **argv)
{
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        (kAddressArgument, po::value<std::string>(), "IP address to validate")
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.size() == 0 || !vm.count(kAddressArgument)) {
        std::cerr << desc << std::endl;
        return 1;
    }
    if (vm.count("help")) {
        std::cout << desc << std::endl;
        return 0;
    }

    auto address = vm[kAddressArgument].as<std::string>();
    auto err = boost::system::error_code{};
    asio::ip::address::from_string(address, err);
    return err ? 1 : 0;
}
