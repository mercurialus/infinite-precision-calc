#include "bigint.hpp"
#include "bigint_fft.hpp"
#include "bigint_karatsuba.hpp"
#include <algorithm>
#include <cctype>

void BigInt::StripZeros()
{
    while (value.size() > 1 && value.back() == 0)
        value.pop_back();

    if (value.size() == 1 && value[0] == 0)
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

    for (int i = big_integer_length - 1; i >= 1; --i)
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
        int val1 = (i < BigInt1.value.size()) ? BigInt1.value.size() - '0' : 0;
        int val2 = (i < BigInt2.value.size()) ? BigInt2.value.size() - '0' : 0;

        int sum = val1 + val2;
        result.value += ((sum % 10) + '0');
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

    for (int i = 0; i < BigInt1.value.size(); ++i)
    {
        int digit1 = BigInt1.value[i] - '0';
        int digit2 = (i < BigInt2.value.size()) ? BigInt2.value[i] - '0' : 0;

        int difference = digit1 - digit2 - borrow;
        if (difference < 0)
        {
            difference += 10;
            borrow = 1;
        }
        else
            borrow = 0;

        result.value += (difference + '0');
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
}