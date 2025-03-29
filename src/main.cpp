#include <iostream>
#include "bigint.hpp" // or appropriate header

int main()
{
    BigInt a("1123123123238090");
    BigInt b("-5123123123412312346110");
    BigInt result1 = a + b;
    BigInt result2 = a - b;

    std::cout << "Result(Addtion): " << result1 << std::endl;
    std::cout << "Result(Subtraction): " << result2 << std::endl;
    return 0;
}
