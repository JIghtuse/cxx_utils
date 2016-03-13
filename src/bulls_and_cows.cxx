#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

vector<int> gen_guess()
{
    constexpr int guess_length{4};

    random_device rd;
    mt19937 gen(rd());

    vector<int> guess{0,1,2,3,4,5,6,7,8,9};
    shuffle(guess.begin(), guess.end(), gen);
    guess.resize(guess_length);

    return guess;
}

// "Bulls and cows" game
int main()
{
    vector<int> secret{gen_guess()};
    vector<int> guess(4);

    cout << "I guessed 4 digits. Try to guess them.\n";

    while (secret != guess) {
        cin >> guess[0] >> guess[1] >> guess[2] >> guess[3];
        if (!cin || !all_of(guess.begin(), guess.end(), [](int i){ return i >= 0 && i <= 9;})) {
            cerr << "Incorrect input. Enter 4 digits separated by space\n";
            continue;
        }

        int bulls{0};
        int cows{0};
        for (size_t i = 0; i < guess.size(); ++i)
            for (size_t j = 0; j < secret.size(); ++j)
                if (guess[i] == secret[j]) {
                    if (i == j)
                        ++bulls;
                    else
                        ++cows;
                }
        if (bulls)
            cout << bulls << " bulls";
        if (bulls && cows)
            cout << " and ";
        if (cows)
            cout << cows << " cows";
        cout << endl;
    }
}
