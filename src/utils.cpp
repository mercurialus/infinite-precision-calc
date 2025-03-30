#include "utils.hpp"

BigInt padRight(BigInt &num, int n)
{
    BigInt padded = num;
    while (padded.size() < n)
        padded.value.push_back('0');
    return padded;
}

std::string padRight(const std::string &x, int n)
{
    std::string padded = x;
    while (padded.size() < n)
        padded.push_back('0');
    return padded;
}
BigInt padLeft(BigInt &num, int n)
{
    BigInt padded = num;
    while (padded.size() < n)
        padded.value.insert(padded.value.begin(), '0'); // prepend '0'
    return padded;
}
std::string padLeft(const std::string &x, int n)
{
    std::string padded = x;
    while (padded.size() < n)
        padded.insert(padded.begin(), '0'); // prepend '0'
    return padded;
}

BigInt mulBy10power_reversed(BigInt &x, int m)
{
    if (x.value == "0" || x.size() == 0)
        return x;

    BigInt result;
    result.value.clear();
    result.value = std::string(m, '0') + x.value;
    return result;
}