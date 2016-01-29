# cxx_utils
Small utilities

## rand_line

Reads a file passed as argument and returns a random line from it:

    $ ./rand_line /usr/share/dict/words
    puddle

## lurker

Simple grep-like utility. Recursively scans current directory for specific
pattern. For now accepts only string and doesn't print anything except matched
lines:

    $ ./lurker random_device
    ./src/bulls_and_cows.cxx
    10:    random_device rd;
    ./src/rand_line.cxx
    26:    random_device rd;

## rand_int

Generates random numbers in specified range:

    $ ./rand_int 1 6 3
    3
    5
    2
    $ ./rand_int -2 2 2
    -1
    2
