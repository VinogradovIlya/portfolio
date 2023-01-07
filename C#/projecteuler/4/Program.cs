using System;
using System.Numerics;

/**
https://projecteuler.net/problem=16

2^15 = 32768 , а сумма его цифр равна 3 + 2 + 7 + 6 + 8 = 26.
Чему равна сумма цифр числа 2^1000?
*/

class Program
{
    static void Main()
    {
        int length = 1000;
        BigInteger num = BigInteger.Pow(2, length);
        BigInteger total = 0;
        while (num != 0)
        {
            BigInteger temp = num % 10;
            total += temp;
            num /= 10;
        }

        System.Console.WriteLine("{0}", total);
    }
}
