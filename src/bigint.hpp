#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>
#include <string>

class BigInt
{
private:
    std::string value; // Will be storing in reverse for ease of implementation
    bool isNegative;

    void StripZeros();
    static BigInt addAbsolute(const BigInt &BigInt1, const BigInt &BigInt2);
    static BigInt subAbsolute(const BigInt &BigInt1, const BigInt &BigInt2);
    static int compareAbsolute(const BigInt &BigInt1, const BigInt &BigInt2);

public:
    // Constructors
    BigInt();
    BigInt(const std::string &number);
    BigInt(int number);

    // Overloading Operators
    BigInt operator+(const BigInt &other) const;
    BigInt operator*(const BigInt &other) const;
    BigInt operator-(const BigInt &other) const;

    bool operator==(const BigInt &other) const;
    bool operator!=(const BigInt &other) const;
    bool operator<(const BigInt &other) const;
    bool operator>(const BigInt &other) const;
    bool operator<=(const BigInt &other) const;
    bool operator>=(const BigInt &other) const;

    // I/O stream overloading
    friend std::ostream &operator<<(std::ostream &out, const BigInt &val);
    friend std::istream &operator>>(std::istream &in, BigInt &val);

    // Maybe I will implement this
    std::string toString() const;
};

#endif /*BIGINT_HPP*/