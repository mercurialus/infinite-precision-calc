#include "bigint.hpp"
// #include "bigint_fft.hpp"
// #include "bigint_karatsuba.hpp"
#include <algorithm>
#include <cctype>

void BigInt::StripZeros()
{
    while (value.size() > 1 && value.back() == '0')
        value.pop_back();

    if (value.size() == 1 && value[0] == '0')
        isNegative = false;
}

BigInt::BigInt() : value("0"), isNegative(false) {}

BigInt::BigInt(int number)
{
    isNegative = number < 0;
    number = std::abs(number);
    value = std::to_string(number);
    std::reverse(value.begin(), value.end());
}

BigInt::BigInt(const std::string &number)
{
    int start = 0; /*If bigint negative -> start=1 else start=0*/

    isNegative = number[0] == '-';

    if (isNegative)
        start = 1;

    value = "";

    int big_integer_length = number.length();

    for (int i = big_integer_length - 1; i >= start; --i)
        if (isdigit(number[i]))
            value += number[i];

    StripZeros();
}

BigInt BigInt::addAbsolute(const BigInt &BigInt1, const BigInt &BigInt2)
{
    BigInt result;
    result.value.clear();

    int carry = 0;
    int maxLen = std::max(BigInt1.value.size(), BigInt2.value.size());

    for (int i = 0; i < maxLen || carry; ++i)
    {
        int val1 = (i < BigInt1.value.size()) ? BigInt1.value[i] - '0' : 0;
        int val2 = (i < BigInt2.value.size()) ? BigInt2.value[i] - '0' : 0;

        int sum = val1 + val2 + carry;
        result.value.push_back(static_cast<char>(sum % 10 + '0'));
        carry = sum / 10;
    }

    result.StripZeros();
    return result;
}

BigInt BigInt::subAbsolute(const BigInt &BigInt1, const BigInt &BigInt2)
{
    BigInt result;
    result.value.clear();

    int borrow = 0;
    int maxSize = std::max(BigInt1.value.size(), BigInt2.value.size());
    for (int i = 0; i < maxSize; ++i)
    {
        int digit1 = (i < BigInt1.value.size()) ? BigInt1.value[i] - '0' : 0;
        int digit2 = (i < BigInt2.value.size()) ? BigInt2.value[i] - '0' : 0;

        int difference = digit1 - digit2 - borrow;
        if (difference < 0)
        {
            difference += 10;
            borrow = 1;
        }
        else
            borrow = 0;

        result.value.push_back(static_cast<char>(difference + '0'));
    }
    result.StripZeros();
    return result;
}

BigInt BigInt::operator+(const BigInt &other) const
{
    /*Both Number are negative return sum and just negate it*/
    if (isNegative == other.isNegative)
    {
        BigInt result = addAbsolute(*this, other);
        result.isNegative = isNegative;
        return result;
    }
    /*If one is negative, sum of them is just difference*/
    else if (compareAbsolute(*this, other) >= 0)
    {
        BigInt result = subAbsolute(*this, other);
        result.isNegative = isNegative;
        return result;
    }
    else
    {
        BigInt result = subAbsolute(other, *this);
        result.isNegative = other.isNegative;
        return result;
    }
}

BigInt BigInt::operator-(const BigInt &other) const
{
    if (isNegative == !other.isNegative)
    {
        BigInt result = addAbsolute(*this, other);
        result.isNegative = isNegative;
        return result;
    }
    else if (compareAbsolute(*this, other) >= 0)
    {
        BigInt result = subAbsolute(*this, other);
        result.isNegative = isNegative;
        return result;
    }
    else
    {
        BigInt result = subAbsolute(other, *this);
        result.isNegative = other.isNegative;
        return result;
    }
}

BigInt BigInt::operator*(const BigInt &other) const
{
    return other;
}

int BigInt::compareAbsolute(const BigInt &BigInt1, const BigInt &BigInt2)
{
    if (BigInt1.value.size() > BigInt2.value.size())
        return 1;
    if (BigInt1.value.size() < BigInt2.value.size())
        return -1;

    for (int i = BigInt1.value.size() - 1; i >= 0; --i)
    {
        if (BigInt1.value[i] > BigInt2.value[i])
            return 1;
        else if (BigInt1.value[i] < BigInt2.value[i])
            return -1;
    }
    return 0;
}

std::ostream &operator<<(std::ostream &out, const BigInt &val)
{
    if (val.isNegative)
        out << "-";
    for (int i = val.value.size() - 1; i >= 0; --i)
        out << val.value[i];
    return out;
}
std::istream &operator>>(std::istream &in, BigInt &val)
{
    std::string s;
    in >> s;
    val = BigInt(s);
    return in;
}