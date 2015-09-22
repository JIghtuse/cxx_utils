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

