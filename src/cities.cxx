#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <experimental/optional>
#include <boost/algorithm/string.hpp>
#include "color.h"

namespace alg = boost::algorithm;
using std::experimental::optional;
using Cities = std::unordered_set<std::string>;

const char* kCitiesDbFile{ "/tmp/cities_db.txt" };

optional<Cities> get_cities(const char* fname)
{
    std::ifstream in{ fname };
    if (!in)
        return optional<Cities>{};

    Cities cities;
    std::move(std::istream_iterator<std::string>{ in },
        std::istream_iterator<std::string>{},
        std::inserter(cities, cities.end()));

    return cities;
}

void save_cities(const char* fname, const Cities& known_cities)
{
    std::ofstream out{ fname };
    if (!out)
        return;

    for (const auto& city : known_cities)
        out << city << '\n';
}

enum class Player {
    Human,
    CPU,
};

// Returns game winner, if any
optional<Player> play(Cities& known_cities)
{
    std::unordered_set<std::string> cities_in_game;
    std::string prev_city;

    auto prompt = [](const std::string& prev) {
        return std::string("City on ") + static_cast<char>(::toupper(prev.back()));
    };
    auto valid_turn = [&prev_city, &cities_in_game](const std::string& city) {
        return !city.empty() && cities_in_game.count(city) == 0
            && prev_city.back() == city.front();
    };

    std::string city;
    auto turn = Player::Human;
    auto winner = optional<Player>{};
    // TODO: loop until interrupted.
    while (!winner) {
        switch (turn) {
        case Player::Human: {
            if (prev_city.empty()) {
                std::cout << "Your turn. City?\n";
                std::cin >> city;
                alg::to_lower(city);

                while (city.empty()) {
                    std::cout << "Invalid name.\n";
                    if (std::cin.eof())
                        return winner;
                    std::cin >> city;
                    alg::to_lower(city);
                }
                known_cities.insert(city);
            }
            else {
                std::cout << "Your turn. " << prompt(prev_city) << "?\n";
                std::cin >> city;
                alg::to_lower(city);

                if (valid_turn(city)) {
                    known_cities.insert(city);
                } else {
                    std::cout << "Not " << prompt(prev_city) << " or we already saw this city.\n";
                    winner = Player::CPU;
                }
            }
            turn = Player::CPU;
            break;
        }
        case Player::CPU: {
            std::cout << "My turn. ";
            auto find = std::find_if(known_cities.begin(), known_cities.end(), valid_turn);
            if (find != known_cities.end()) {
                auto reply = city = *find;
                reply.front() = ::toupper(reply.front());
                std::cout << prompt(prev_city) << ": " << reply << std::endl;
            }
            else {
                std::cout << "I know no " << prompt(prev_city) << ".\n";
                winner = Player::Human;
            }
            turn = Player::Human;
            break;
        }
        default:
            return winner;
        }
        cities_in_game.insert(city);
        prev_city = city;
    }
    return winner;
}

// 'Cities' game
int main()
{
    auto known_cities = get_cities(kCitiesDbFile);
    if (!known_cities || known_cities->size() == 0) {
        std::cout << "I know no cities.\n";
        return 1;
    }
    else {
        std::cout << "I know " << known_cities->size() << " cities.\n";
    }

    auto winner = play(*known_cities);
    if (!winner) {
        std::cout << "No winner.\n";
    } else {
        switch (*winner) {
        case Player::Human:
            std::cout << Color::Green << "You win!\n" << Color::None;
            break;
        case Player::CPU:
            std::cout << Color::Red << "I win!\n" << Color::None;
            break;
        default:
            throw std::runtime_error("unreachable");
        }
    }

    save_cities(kCitiesDbFile, *known_cities);
}
