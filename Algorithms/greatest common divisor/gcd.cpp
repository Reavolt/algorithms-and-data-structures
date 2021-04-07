#include <iostream>
#include "profile.h"

//-------------------------------------------------------------------------------------------------
unsigned int gcd_1(unsigned int a, unsigned int b);
unsigned int gcd_2(unsigned int a, unsigned int b);
unsigned int gcd_3(unsigned int a, unsigned int b);
unsigned int gcd_4(unsigned int a, unsigned int b);
//-------------------------------------------------------------------------------------------------
int main()
{
    {
        LOG_DURATION("GCD dividing")
        std::cout << "GCD dividing = " << gcd_1(85673534, 342542) << std::endl;
    }
    {
        LOG_DURATION("GCD by subtraction")
        std::cout << "GCD by subtraction = " << gcd_2(85673534, 342542) << std::endl;
    }
    {
        LOG_DURATION("GCD by recursion")
        std::cout << "GCD by recursion = " << gcd_3(85673534, 342542) << std::endl;
    }
    {
        LOG_DURATION("GCD Binary algorithm")
        std::cout << "GCD Binary algorithm = " << gcd_4(85673534, 342542) << std::endl;
    }
    return 0;
}
//-------------------------------------------------------------------------------------------------
unsigned int gcd_1(unsigned int a, unsigned int b)
{
    if (a == b)
    {
        return a;
    }

    if (a == 0)
    {
        return b;
    }

    if (b == 0)
    {
        return a;
    }

    while(a != 0 && b != 0)
    {
        if (a > b)
        {
            a = a % b;
        }
        else
        {
            b = b % a;
        }
    }
    return a + b;
}
//-------------------------------------------------------------------------------------------------
unsigned int gcd_2(unsigned int a, unsigned int b)
{
    if (a == b)
    {
        return a;
    }

    if (a == 0)
    {
        return b;
    }

    if (b == 0)
    {
        return a;
    }

    while(a != b)
    {
        if (a > b)
        {
            a = a - b;
        }
        else
        {
            b = b - a;
        }
    }
    return b;
}
//-------------------------------------------------------------------------------------------------
unsigned int gcd_3(unsigned int a, unsigned int b)
{
    if(b == 0)
    {
        return a;
    }
    return gcd_3(b, a % b);
}
//-------------------------------------------------------------------------------------------------
unsigned int gcd_4(unsigned int a, unsigned int b)
{
    if (a == b)
    {
        return a;
    }

    if (a == 0)
    {
        return b;
    }

    if (b == 0)
    {
        return a;
    }

    if (~a & 1u)
    {
        if (b & 1u)
        {
            return gcd_4(a >> 1u, b);
        }
        else
        {
            return gcd_4(a >> 1u, b >> 1u) << 1u;
        }

    }

    if (~b & 1u)
    {
        return gcd_4(a, b >> 1u);
    }

    if (a > b)
    {
        return gcd_4((a - b) >> 1u, b);
    }
    return gcd_4((b - a) >> 1u, a);
}
//-------------------------------------------------------------------------------------------------