#ifndef UTILS_HPP
#define UTILS_HPP

#include "bigint.hpp"

BigInt mulBy10power_reversed(BigInt &x, int m);
BigInt padRight(BigInt &x, int n);
std::string padRight(std::string &x, int n);

#endif