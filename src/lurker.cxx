#include <boost/filesystem.hpp>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;
namespace fs = boost::filesystem;

enum class Extension {
    C,
    CXX,
};

using ExtensionDict = std::map<Extension, vector<string>>;

struct Match {
    size_t lineno;
    string s;
};

vector<Match> grep_in_file(const char* filename, const char* pattern)
{
    vector<Match> matches;

    size_t lineno{0};
    ifstream ifs(filename);
    for (string s; getline(ifs, s);) {
        ++lineno;
        if (s.find(pattern) != string::npos)
            matches.push_back(Match{lineno, s});
    }
    return matches;
}

void print_matches(const char* filename, const vector<Match>& matches)
{
    cout << filename << endl;
    for (const Match& match : matches)
        cout << match.lineno << ":" << match.s << endl;
}

bool has_str(const vector<string>& haystack, const string& needle)
{
    auto p = find(haystack.begin(), haystack.end(), needle);
    return p != haystack.end();
}

/* Looks for @pattern in current directory and subdirectories files
 * Returns 0 if there were some matches, 1 otherwise */
int grep_recursively(const vector<string>& extensions, const char* pattern)
{
    bool was_matches{false};
    fs::path search_path(".");

    for (const auto element : fs::recursive_directory_iterator(search_path)) {
        fs::path p = element;
        if (is_regular_file(p) && has_str(extensions, p.extension().string())) {
            const auto matches = grep_in_file(p.c_str(), pattern);
            if (!matches.empty()) {
                was_matches = true;
                print_matches(p.c_str(), matches);
            }
        }
    }
    return !was_matches;
}

/* grep-like tool to search in specific files */
int main(int argc, char *argv[])
{
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " pattern\n";
        return 1;
    }

    ExtensionDict extensions{
        {Extension::C,   {".c"} },
        {Extension::CXX, {".cxx", ".cc", ".cpp"}},
    };

    return grep_recursively(extensions[Extension::CXX], argv[1]);
}
