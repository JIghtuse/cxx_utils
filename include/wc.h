#pragma once

#include <iostream>

std::tuple<size_t, size_t, size_t> get_counts(std::istream& in);

// prints wc-like count statistics of @in to @out
void print_counts(std::istream& in, std::ostream& out);
