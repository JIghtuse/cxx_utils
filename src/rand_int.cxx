#include <experimental/random>
#include <experimental/optional>
#include <iostream>
#include <random>
#include <sstream>

using namespace std;
using std::experimental::optional;

class RandomInt {
public:
    RandomInt(int from, int to) :
        re{},
        dist{from, to}
    {}
    int operator()()
    {
        return dist(re);
    }
private:
    default_random_engine re;
    uniform_int_distribution<int> dist;
};

template<typename T>
optional<T> parse_number(const string& s)
{
    T value;
    istringstream iss{s};

    if (iss >> value)
        return value;
    return optional<T>{};
}

template<typename T>
T parse_number_with_default(const string& s, T default_value)
{
    auto n = parse_number<T>(s);
    if (n)
        return *n;
    return default_value;
}

int main(int argc, char *argv[])
{
    auto usage = [argv]() {
        cerr << "Usage: " << argv[0]
             << " <from_number> <to_number> [nnumbers =1]\n";
    };
    if (argc < 3 || argc > 4) {
        usage();
        return 1;
    }

    const auto from = parse_number<int>(argv[1]);
    const auto to = parse_number<int>(argv[2]);
    if (!from || !to) {
        usage();
        return 1;
    }
    size_t nnumbers = 1;
    if (argc == 4)
        nnumbers = parse_number_with_default<size_t>(argv[3], nnumbers);

#ifdef __cpp_lib_experimental_randint
    for (size_t i = 0; i < nnumbers; ++i)
        cout << std::experimental::randint(*from, *to) << '\n';
#else
    RandomInt ri{*from, *to};
    for (size_t i = 0; i < nnumbers; ++i)
        cout << ri() << '\n';
#endif

    return 0;
}
