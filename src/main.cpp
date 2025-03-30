#include <iostream>
#include "bigint.hpp" // or appropriate header
#include "bigint_karatsuba.hpp"
#include <chrono>

int main()
{
    BigInt big1("9" + std::string(199, '9')); // 200-digit number: 999...999
    BigInt big2("9" + std::string(199, '9'));

    auto start_naive = std::chrono::high_resolution_clock::now();
    BigInt res_naive = big1 * big2;
    auto end_naive = std::chrono::high_resolution_clock::now();
    auto duration_naive = std::chrono::duration_cast<std::chrono::milliseconds>(end_naive - start_naive).count();

    auto start_karatsuba = std::chrono::high_resolution_clock::now();
    BigInt res_karat = karatsubaMultiply(big1, big2);
    auto end_karatsuba = std::chrono::high_resolution_clock::now();
    auto duration_karatsuba = std::chrono::duration_cast<std::chrono::milliseconds>(end_karatsuba - start_karatsuba).count();

    std::cout << "\nNaive took: " << duration_naive << " ms" << std::endl;
    std::cout << "Karatsuba took: " << duration_karatsuba << " ms" << std::endl;
    std::cout << "Same result? " << (res_naive == res_karat ? "Yes" : "No") << std::endl;
}
