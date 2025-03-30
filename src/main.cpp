#include <iostream>
#include "bigint.hpp" // or appropriate header
#include "bigint_karatsuba.hpp"

int main()
{
    BigInt a("500");
    BigInt b("1000");
    BigInt result1 = a + b;
    BigInt result2 = a - b;
    BigInt result3 = a * b;
    BigInt result4 = karatsubaMultiply(a, b);

    std::cout << "Result(Addtion): " << result1 << std::endl;
    std::cout << "Result(Subtraction): " << result2 << std::endl;
    std::cout << "Result(Multiplication): " << result3 << std::endl;
    std::cout << "Result(Karatsuba Multiplication): " << result4 << std::endl;
    return 0;
}
