#include "bigint_karatsuba.hpp"
#include <algorithm>
#include <string>

/*
  We'll do the standard "MSD-first" Karatsuba by:
  1) Reverse LSD-first to get a normal MSD-first string
  2) Karatsuba in MSD-first
  3) Convert back to LSD-first
*/

static std::string reverseString(const std::string &s)
{
    return std::string(s.rbegin(), s.rend());
}

// Classic Karatsuba on MSD-first decimal strings
// Returns an MSD-first string of the product
static std::string karatsubaMSD(const std::string &A, const std::string &B);

BigInt karatsubaMultiply(const BigInt &x, const BigInt &y)
{
    // Base or zero check
    if (x.size() < 32 && y.size() < 32)
        return BigInt(x * y);
    if (x.value == "0" || y.value == "0")
        return BigInt("0");

    // Convert LSD-first => MSD-first
    std::string A = reverseString(x.value);
    std::string B = reverseString(y.value);

    // Karatsuba in MSD-first
    std::string productMSD = karatsubaMSD(A, B);

    // Convert back to LSD-first
    // if productMSD == "0", just return 0
    if (productMSD == "0")
        return BigInt("0");

    // else build LSD-first from MSD-first
    std::reverse(productMSD.begin(), productMSD.end());

    BigInt result;
    result.isNegative = (x.isNegative != y.isNegative);
    result.value = productMSD;
    result.StripZeros();
    if (result.value == "0") // special case
        result.isNegative = false;

    return result;
}

/*****************************************************************
   Actual Karatsuba for MSD-first strings
 *****************************************************************/
static std::string trimLeadingZeros(const std::string &s)
{
    int idx = 0;
    while (idx < (int)s.size() && s[idx] == '0')
        idx++;
    if (idx == (int)s.size())
        return "0";
    return s.substr(idx);
}

// Simple add for MSD-first
static std::string addMSD(const std::string &A, const std::string &B)
{
    std::string a = trimLeadingZeros(A);
    std::string b = trimLeadingZeros(B);
    if (a == "0")
        return b;
    if (b == "0")
        return a;

    int carry = 0;
    int i = (int)a.size() - 1, j = (int)b.size() - 1;
    std::string result;
    while (i >= 0 || j >= 0 || carry)
    {
        int x = (i >= 0 ? (a[i] - '0') : 0);
        int y = (j >= 0 ? (b[j] - '0') : 0);
        int s = x + y + carry;
        carry = s / 10;
        s = s % 10;
        result.push_back(char(s + '0'));
        i--;
        j--;
    }
    std::reverse(result.begin(), result.end());
    return trimLeadingZeros(result);
}

// Sub for MSD-first (assume A >= B)
static std::string subMSD(const std::string &A, const std::string &B)
{
    std::string a = trimLeadingZeros(A);
    std::string b = trimLeadingZeros(B);
    // assume a >= b
    if (a == b)
        return "0";

    int carry = 0;
    int i = (int)a.size() - 1, j = (int)b.size() - 1;
    std::string result;
    while (i >= 0 || j >= 0)
    {
        int x = (i >= 0 ? a[i] - '0' : 0);
        int y = (j >= 0 ? b[j] - '0' : 0);
        int diff = x - y - carry;
        if (diff < 0)
        {
            diff += 10;
            carry = 1;
        }
        else
        {
            carry = 0;
        }
        result.push_back(char(diff + '0'));
        i--;
        j--;
    }
    while (result.size() > 1 && result.back() == '0')
        result.pop_back();
    std::reverse(result.begin(), result.end());
    return trimLeadingZeros(result);
}

static std::string mult10pow(const std::string &s, int p)
{
    if (s == "0")
        return "0";
    return s + std::string(p, '0');
}

static std::string karatsubaMSD(const std::string &A, const std::string &B)
{
    // remove leading zeros
    std::string a = trimLeadingZeros(A);
    std::string b = trimLeadingZeros(B);
    if (a == "0" || b == "0")
        return "0";

    // base case
    if (a.size() == 1 && b.size() == 1)
    {
        int d = (a[0] - '0') * (b[0] - '0');
        return std::to_string(d);
    }

    // ensure same length, even
    int n = std::max(a.size(), b.size());
    if (n % 2 != 0)
        n++;
    while ((int)a.size() < n)
        a.insert(a.begin(), '0');
    while ((int)b.size() < n)
        b.insert(b.begin(), '0');

    int m = n / 2;
    // split a = a1 * 10^m + a0
    // a1 = left half, a0 = right half
    std::string a1 = a.substr(0, n - m);
    std::string a0 = a.substr(n - m);
    std::string b1 = b.substr(0, n - m);
    std::string b0 = b.substr(n - m);

    // z2 = a1*b1
    // z0 = a0*b0
    // z1 = (a1+a0)*(b1+b0) - z2 - z0
    std::string z2 = karatsubaMSD(a1, b1);
    std::string z0 = karatsubaMSD(a0, b0);
    std::string sumA = addMSD(a1, a0);
    std::string sumB = addMSD(b1, b0);
    std::string z1 = subMSD(subMSD(karatsubaMSD(sumA, sumB), z2), z0);

    // combine => z2 * 10^(2*m) + z1 * 10^m + z0
    std::string r = addMSD(addMSD(mult10pow(z2, m * 2), mult10pow(z1, m)), z0);

    return trimLeadingZeros(r);
}
