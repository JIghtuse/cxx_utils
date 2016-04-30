#include <iostream>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

void print_directory_listing(const fs::path& dir)
{
    std::cout << dir.c_str() << ":\n";
    for (auto& p: fs::directory_iterator(dir)) {
        std::cout << p.path().filename().c_str() << '\n';
    }
}

void print_file_listing(const fs::path& file)
{
    std::cout << file.c_str() << '\n';
}

int main(int argc, char **argv)
{
    if (argc == 1) {
        print_directory_listing(".");
    } else {
        for (auto i = 1; i < argc; ++i) {
            try {
                if (fs::is_directory(argv[i])) {
                    print_directory_listing(argv[i]);
                } else {
                    print_file_listing(argv[i]);
                }
            } catch (fs::filesystem_error& e) {
                std::cerr << e.what() << '\n';
            }
        }
    }
}
