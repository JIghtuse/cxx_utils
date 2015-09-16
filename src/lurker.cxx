#include <boost/filesystem.hpp>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

using namespace std;
namespace fs = boost::filesystem;

enum class Extension {
    CXX
};

using ExtensionDict = std::map<Extension, string>;

void grep_in_file(const char* filename, const char* pattern)
{
    ifstream ifs(filename);
    for (string s; getline(ifs, s);)
        if (s.find(pattern) != string::npos)
            cout << s << endl;
}

void grep_recursively(ExtensionDict& extensions, Extension ext, const char* pattern)
{
    const string search_extension{extensions[ext]};
    fs::path search_path(".");

    for (auto element : fs::recursive_directory_iterator(search_path)) {
        fs::path p = element;
        if (is_regular_file(p) && p.extension() == search_extension)
            grep_in_file(p.c_str(), pattern);
    }
}

/* grep-like tool to search in specific files */
int main()
{
    ExtensionDict extensions;
    extensions[Extension::CXX] = ".cxx";

    grep_recursively(extensions, Extension::CXX, "string");

    return 0;
}
