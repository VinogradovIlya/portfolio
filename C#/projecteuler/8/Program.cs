using System;
using System.Collections.Generic;
using System.Numerics;

/**
https://projecteuler.net/problem=29

Рассмотрим все целочисленные комбинации a^b для 2 ≤ a ≤ 5 и 2 ≤ b ≤ 5:
2^2 = 4, 2^3 = 8, 2^4 = 16, 2^5 = 32
3^2 = 9, 3^3 = 27, 3^4 = 81, 3^5 = 243
4^2 = 16, 4^3 = 64, 4^4 = 256, 4^5 = 1024
5^2 = 25, 5^3 = 125, 5^4 = 625, 5^5 = 3125

Если затем расположить их в числовом порядке, удалив любые повторы,
то мы получим следующую последовательность из 15 различных терминов:
4, 8, 9, 16, 25, 27, 32, 64, 81, 125, 243, 256, 625, 1024, 3125
Сколько различных терминов содержится в последовательности, порожденной a^b для 2 ≤ a ≤ 100 и 2 ≤ b ≤ 100?
*/

class Program
{
    static void Main()
    {
        int a, b;
        List<BigInteger> lst = new List<BigInteger>();

        for (a = 2; a <= 100; a++)
        {
            for (b = 2; b <= 100; b++)
            {
                BigInteger result = BigInteger.Pow(a, b);
                if (lst.IndexOf(result) == -1) lst.Add(result);
            }
        }
        System.Console.WriteLine(lst.Count);
    }
}