using System;
using System.Numerics;

/**
https://projecteuler.net/problem=20

n! означает n × ( n - 1) × ... × 3 × 2 × 1
Например, 10! = 10×9×…×3×2×1 = 3628800,
а сумма цифр в числе 10! равно 3 + 6 + 2 + 8 + 8 + 0 + 0 = 27.
Найдите сумму цифр в числе 100!
*/

class Program
{
    static void Main()
    {
        int n = 100;

        BigInteger Factorial(BigInteger number)
        {
            if (number == 1) return 1;
            return number *= Factorial(number - 1);
        }

        BigInteger SumNumber(BigInteger number)
        {
            BigInteger result = 0;
            while (number > 0)
            {
                BigInteger step1 = number % 10;
                number /= 10;
                result += step1;
            }
            return result;
        }
        
        System.Console.WriteLine(
            SumNumber(
                Factorial(n)));
    }
}
