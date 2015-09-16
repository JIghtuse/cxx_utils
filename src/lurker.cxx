#include <boost/filesystem.hpp>
#include <iostream>

using namespace std;
using namespace boost::filesystem;

/* investigates file system */
int main()
{
    path search_path(".");

    cout << "directory " << search_path << " contents: \n";
    // for (auto element: search_path)
        // cout << "\t" << element << endl;
    return 0;
}
