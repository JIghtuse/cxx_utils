#include <cassert>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using namespace std;

// Reads entire file into vector line by line
vector<string> read_file(const string& path)
{
    vector<string> lines;
    ifstream ifs(path, ios_base::in);
    for (string s; getline(ifs, s);)
        lines.push_back(s);

    return lines;
}

// Returns random line from a vector of lines
string get_random_line(const vector<string>& lines)
{
    assert(!lines.empty());

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist (0, lines.size() - 1);

    return lines[dist(gen)];
}

// Prints random line from a file
int main(int argc, char *argv[])
{
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " filename.txt\n";
        return 1;
    }

    const string& fname = argv[1];

    const auto& lines = read_file(fname);
    if (lines.empty()) {
        cerr << "File '" << fname << "' is empty or unavailable\n";
        return 1;
    }

    cout << get_random_line(lines) << endl;
}
