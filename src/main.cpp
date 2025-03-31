#include <iostream>
#include <sstream>
#include <cstdlib>
#include "bigint.hpp"

// Helper function that prints a short message and exits if the test fails.
void runTest(const std::string &label, const BigInt &result, const std::string &expected)
{
    std::stringstream ss;
    ss << result;
    std::string resStr = ss.str();
    std::cout << label << " | Exp: " << expected << " | Got: " << resStr << std::endl;
    if (resStr != expected)
    {
        std::cerr << "Test failed: " << label << std::endl;
        exit(1);
    }
}

int main()
{
    // Addition/Subtraction basic examples
    {
        BigInt a("10");
        BigInt b("5");
        runTest("TC1: 5-10", b - a, "-5");
        runTest("TC2: 5+10", b + a, "15");
    }

    // Larger positive values
    {
        BigInt x("12345678901234567890");
        BigInt y("98765432109876543210");
        runTest("TC3: x+y", x + y, "111111111011111111100");
        runTest("TC4: y-x", y - x, "86419753208641975320");
    }

    // Positive vs. Negative
    {
        BigInt neg("100");
        BigInt pos("75");
        runTest("TC5: 75-100", pos - neg, "-25");
        runTest("TC6: 100-75", neg - pos, "25");
    }

    // Zero Cases
    {
        BigInt zero("0");
        runTest("TC7: 0-0", zero - zero, "0");
        runTest("TC8: 0+0", zero + zero, "0");
    }

    // Zero with positive & negative operands
    {
        BigInt z("0");
        BigInt p("12345");
        BigInt n("-6789");
        runTest("TC9: 0+12345", z + p, "12345");
        runTest("TC10: 0+ -6789", z + n, "-6789");
        runTest("TC11: 0-12345", z - p, "-12345");
        runTest("TC12: 0- -6789", z - n, "6789");
    }

    // Negative + Negative & Subtraction
    {
        BigInt n1("-1000");
        BigInt n2("-2000");
        runTest("TC13: -1000+ -2000", n1 + n2, "-3000");
        runTest("TC14: -2000- -1000", n2 - n1, "-1000");
    }

    // Same Magnitude, Opposite Sign
    {
        BigInt x("987654321");
        BigInt y("-987654321");
        runTest("TC15: 987654321+ -987654321", x + y, "0");
        runTest("TC16: 987654321- -987654321", x - y, "1975308642");
        runTest("TC17: -987654321-987654321", y - x, "-1975308642");
    }

    // Equal Values with Different Signs
    {
        BigInt a1("99999999");
        BigInt a2("-99999999");
        runTest("TC18: 99999999-99999999", a1 - a1, "0");
        runTest("TC19: -99999999- -99999999", a2 - a2, "0");
        runTest("TC20: 99999999+ -99999999", a1 + a2, "0");
    }

    // Very Large Number Tests
    {
        BigInt big1("1000000000000000000000000000000");
        BigInt big2("1");
        runTest("TC21: big1+1", big1 + big2, "1000000000000000000000000000001");
        runTest("TC22: big1-1", big1 - big2, "999999999999999999999999999999");
        runTest("TC23: 1-big1", big2 - big1, "-999999999999999999999999999999");
    }

    // Repeated Add/Sub (Loop)
    {
        BigInt inc("1");
        BigInt result("0");
        for (int i = 0; i < 1000; ++i)
            result = result + inc;
        runTest("TC24: Sum 1 (1000 times)", result, "1000");
        for (int i = 0; i < 500; ++i)
            result = result - inc;
        runTest("TC25: Subtract 1 (500 times)", result, "500");
    }

    // Negative - Negative
    {
        BigInt n1("-400");
        BigInt n2("-100");
        runTest("TC26: -400- -100", n1 - n2, "-300");
        runTest("TC27: -100- -400", n2 - n1, "300");
    }

    // Multiplication Tests (Basic and Zero)
    {
        runTest("TC28: 5*10", BigInt("5") * BigInt("10"), "50");
        runTest("TC29: -5*10", BigInt("-5") * BigInt("10"), "-50");
        runTest("TC30: 5*-10", BigInt("5") * BigInt("-10"), "-50");
        runTest("TC31: -5*-10", BigInt("-5") * BigInt("-10"), "50");
        runTest("TC32: 0*12345", BigInt("0") * BigInt("12345"), "0");
        runTest("TC33: 12345*0", BigInt("12345") * BigInt("0"), "0");
        runTest("TC34: 0*-6789", BigInt("0") * BigInt("-6789"), "0");
        runTest("TC35: 12345678901234567890*0", BigInt("12345678901234567890") * BigInt("0"), "0");
    }

    // Additional Addition/Subtraction tests
    {
        runTest("TC36: 999+1", BigInt("999") + BigInt("1"), "1000");
        runTest("TC37: 500+500", BigInt("500") + BigInt("500"), "1000");
        runTest("TC38: 123456789+987654321", BigInt("123456789") + BigInt("987654321"), "1111111110");
        runTest("TC39: 1000-1", BigInt("1000") - BigInt("1"), "999");
        runTest("TC40: 1000-1000", BigInt("1000") - BigInt("1000"), "0");
        runTest("TC41: 1-1000", BigInt("1") - BigInt("1000"), "-999");
    }

    // Additional Multiplication tests
    {
        runTest("TC42: 123456789*987654321", BigInt("123456789") * BigInt("987654321"), "121932631112635269");
        runTest("TC43: 111111111*111111111", BigInt("111111111") * BigInt("111111111"), "12345679012345621");
        runTest("TC44: 99999*99999", BigInt("99999") * BigInt("99999"), "9999800001");
        runTest("TC45: 12345*6789", BigInt("12345") * BigInt("6789"), "83810205");
    }

    // Tests with Leading Zeros
    {
        runTest("TC46: 000123+000456", BigInt("000123") + BigInt("000456"), "579");
        runTest("TC47: 000500-000123", BigInt("000500") - BigInt("000123"), "377");
        runTest("TC48: 00012*00034", BigInt("00012") * BigInt("00034"), "408");
    }

    // More Subtraction and Addition with Negatives
    {
        runTest("TC49: -12345-67890", BigInt("-12345") - BigInt("67890"), "-80235");
        runTest("TC50: -12345+67890", BigInt("-12345") + BigInt("67890"), "55545");
    }

    // More Multiplication with Negatives
    {
        runTest("TC51: -123*456", BigInt("-123") * BigInt("456"), "-56088");
        runTest("TC52: 123*-456", BigInt("123") * BigInt("-456"), "-56088");
        runTest("TC53: -123*-456", BigInt("-123") * BigInt("-456"), "56088");
    }

    // Very Large Addition/Subtraction
    {
        runTest("TC54: 999999999999999999999+1", BigInt("999999999999999999999") + BigInt("1"), "1000000000000000000000");
        runTest("TC55: 1000000000000000000000-1", BigInt("1000000000000000000000") - BigInt("1"), "999999999999999999999");
    }

    // Very Large Multiplication
    {
        runTest("TC56: 100000000000000000000*10", BigInt("100000000000000000000") * BigInt("10"), "1000000000000000000000");
        runTest("TC57: 100000000000000000000*0", BigInt("100000000000000000000") * BigInt("0"), "0");
    }

    // Repeated addition (500 times)
    {
        BigInt sum("0");
        for (int i = 0; i < 500; ++i)
            sum = sum + BigInt("1");
        runTest("TC58: Sum 1 (500 times)", sum, "500");
    }

    // Repeated multiplication: multiply by 2 ten times (2^10 = 1024)
    {
        BigInt prod("1");
        for (int i = 0; i < 10; ++i)
            prod = prod * BigInt("2");
        runTest("TC59: 1*2^10", prod, "1024");
    }

    // Repeated multiplication: multiply by 3 five times (3^5 = 243)
    {
        BigInt prod("1");
        for (int i = 0; i < 5; ++i)
            prod = prod * BigInt("3");
        runTest("TC60: 1*3^5", prod, "243");
    }

    // Chain Addition
    {
        BigInt a("100");
        a = a + BigInt("200");
        a = a + BigInt("300");
        runTest("TC61: 100+200+300", a, "600");
    }

    // Simple Subtraction
    {
        runTest("TC62: 1000-2000", BigInt("1000") - BigInt("2000"), "-1000");
    }

    // More Simple Multiplication
    {
        runTest("TC63: 50*50", BigInt("50") * BigInt("50"), "2500");
        runTest("TC64: 12345678901234567890*1", BigInt("12345678901234567890") * BigInt("1"), "12345678901234567890");
        runTest("TC65: 12345678901234567890*-1", BigInt("12345678901234567890") * BigInt("-1"), "-12345678901234567890");
        runTest("TC66: -12345678901234567890*-1", BigInt("-12345678901234567890") * BigInt("-1"), "12345678901234567890");
        runTest("TC67: 999*999", BigInt("999") * BigInt("999"), "998001");
    }

    // Additional Negative Addition
    {
        runTest("TC68: -500+ -500", BigInt("-500") + BigInt("-500"), "-1000");
    }

    // Subtraction resulting in zero
    {
        runTest("TC69: 500-500", BigInt("500") - BigInt("500"), "0");
    }

    // Multiplication with Zero
    {
        runTest("TC70: 123456789*0", BigInt("123456789") * BigInt("0"), "0");
        runTest("TC71: 0*987654321", BigInt("0") * BigInt("987654321"), "0");
    }

    // Multiplication: 98765 * 43210
    {
        runTest("TC72: 98765*43210", BigInt("98765") * BigInt("43210"), "4267635650");
    }

    // Complex very large Addition/Subtraction
    {
        runTest("TC73: 123456789012345678901234567890+987654321098765432109876543210",
                BigInt("123456789012345678901234567890") + BigInt("987654321098765432109876543210"),
                "1111111110111111111011111111100");
        runTest("TC74: 987654321098765432109876543210-123456789012345678901234567890",
                BigInt("987654321098765432109876543210") - BigInt("123456789012345678901234567890"),
                "864197532086419753208641975320");
    }

    // More Large Multiplication
    {
        runTest("TC75: 1234567890*9876543210",
                BigInt("1234567890") * BigInt("9876543210"),
                "12193263111263526900");
        runTest("TC76: 999999999*999999999",
                BigInt("999999999") * BigInt("999999999"),
                "999999998000000001");
    }

    // Multiplication with repeating ones
    {
        runTest("TC77: 111111111111111111*1",
                BigInt("111111111111111111") * BigInt("1"),
                "111111111111111111");
        runTest("TC78: 111111111111111111*-1",
                BigInt("111111111111111111") * BigInt("-1"),
                "-111111111111111111");
        runTest("TC79: -111111111111111111*-1",
                BigInt("-111111111111111111") * BigInt("-1"),
                "111111111111111111");
    }

    // More Addition/Subtraction with large numbers
    {
        runTest("TC80: 1000000000000000000+1000000000000000000",
                BigInt("1000000000000000000") + BigInt("1000000000000000000"),
                "2000000000000000000");
        runTest("TC81: 1000000000000000000-1000000000000000000",
                BigInt("1000000000000000000") - BigInt("1000000000000000000"),
                "0");
    }

    // Very large Multiplication
    {
        runTest("TC82: 1000000000000000000*1000000000000000000",
                BigInt("1000000000000000000") * BigInt("1000000000000000000"),
                "1000000000000000000000000000000000000");
    }

    // Negative large number tests
    {
        runTest("TC83: -1000000000000000000+ -1000000000000000000",
                BigInt("-1000000000000000000") + BigInt("-1000000000000000000"),
                "-2000000000000000000");
        runTest("TC84: -1000000000000000000-1000000000000000000",
                BigInt("-1000000000000000000") - BigInt("1000000000000000000"),
                "-2000000000000000000");
        runTest("TC85: -1000000000000000000*1000000000000000000",
                BigInt("-1000000000000000000") * BigInt("1000000000000000000"),
                "-1000000000000000000000000000000000000");
    }

    // Single Digit Operations
    {
        runTest("TC86: 7+8", BigInt("7") + BigInt("8"), "15");
        runTest("TC87: 7-8", BigInt("7") - BigInt("8"), "-1");
        runTest("TC88: 7*8", BigInt("7") * BigInt("8"), "56");
        runTest("TC89: 7*-8", BigInt("7") * BigInt("-8"), "-56");
        runTest("TC90: -7*8", BigInt("-7") * BigInt("8"), "-56");
        runTest("TC91: -7*-8", BigInt("-7") * BigInt("-8"), "56");
    }

    // More Negative Operations
    {
        runTest("TC92: -999999999+1", BigInt("-999999999") + BigInt("1"), "-999999998");
        runTest("TC93: -999999999-1", BigInt("-999999999") - BigInt("1"), "-1000000000");
    }

    // Another Multiplication Zero test
    {
        runTest("TC94: 0*0", BigInt("0") * BigInt("0"), "0");
    }

    // A couple more simple addition/subtraction tests
    {
        runTest("TC95: 42+58", BigInt("42") + BigInt("58"), "100");
        runTest("TC96: 42-58", BigInt("42") - BigInt("58"), "-16");
    }

    // Additional Multiplication tests
    {
        runTest("TC97: 100000001*100000001",
                BigInt("100000001") * BigInt("100000001"),
                "10000000200000001");
        runTest("TC98: 12345*67890",
                BigInt("12345") * BigInt("67890"),
                "838102050");
    }

    // Final Tests
    {
        // Using a lambda to compute repeated addition (1 added 100 times)
        runTest("TC99: 1 added 100 times", []()
                {
            BigInt sum("0");
            for (int i = 0; i < 100; ++i)
                sum = sum + BigInt("1");
            return sum; }(), "100");
        runTest("TC100: 0*0", BigInt("0") * BigInt("0"), "0");
    }

    std::cout << "All tests passed." << std::endl;
    return 0;
}
