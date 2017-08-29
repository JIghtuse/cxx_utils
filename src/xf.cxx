#include <iostream>
#include <string>
#include <boost/program_options.hpp>
#include <experimental/string_view>
#include <experimental/filesystem>

namespace po = boost::program_options;
namespace fs = std::experimental::filesystem;
using std::experimental::string_view;

namespace {

constexpr auto kHelpArgumentName = "help";
constexpr auto kFilenameArgumentName = "filename";

} // anonymous namespace

enum class FileType {
    Rar,
    Tar,
    Unknown,
    Zip,
};

FileType DetermineFileType(const fs::path&)
{
    return FileType::Unknown;
}

bool Unpack(const fs::path& path)
{
    auto type = DetermineFileType(path);
    if (type == FileType::Unknown) {
        std::cerr << path << " has unknown archive format" << '\n';
        return false;
    }
    std::cout << "unpacking " << path << '\n';
    return true;
}

int main(int argc, char **argv)
{
    po::options_description desc("Allowed options");
    desc.add_options()
        (kHelpArgumentName, "produce help message")
        (kFilenameArgumentName, po::value<std::string>(), "archive file to unpack")
    ;

    auto vm = po::variables_map{};
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.size() == 0) {
        std::cout << desc << std::endl;
        return 1;
    }
    if (vm.count(kHelpArgumentName)) {
        std::cout << desc << std::endl;
        return 0;
    }

    auto path = vm[kFilenameArgumentName].as<std::string>();
    Unpack(path);
}
