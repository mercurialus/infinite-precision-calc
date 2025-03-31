#include <iostream>
#include "bigint.hpp" // or appropriate header
#include <chrono>

int main()
{
    BigInt big1("1" + std::string(999999, '1')); // 200-digit number: 999...999
    BigInt big2("1" + std::string(999999, '1'));

    auto start_naive = std::chrono::high_resolution_clock::now();
    BigInt res_naive = big1 * big2;
    auto end_naive = std::chrono::high_resolution_clock::now();
    auto duration_naive = std::chrono::duration_cast<std::chrono::milliseconds>(end_naive - start_naive).count();
    std::cout << "\nNaive took: " << duration_naive << " ms" << std::endl;
}