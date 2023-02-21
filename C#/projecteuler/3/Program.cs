using System;

/**
https://projecteuler.net/problem=9

Пифагорова тройка — это набор из трех натуральных чисел, a < b < c , для которых
a^2 + b^2 == c^2
Существует ровно одна пифагорейская тройка, для которой a + b + c = 1000.
Найдите произведение abc.
*/

class Program
{
    static void Main()
    {
        // DateTime StartTime;
        // StartTime = DateTime.Now;
        int number = 1000;

        for (int a = 1; a < number; a++)
        {
            for (int b = a + 1; b < number; b++)
            {
                int c = (int)Math.Sqrt(a * a + b * b);
                if (c > b && a + b + c == number && c * c == a * a + b * b)
                    System.Console.WriteLine("{0}", a * b * c);
                break;
            }
        }

        // DateTime EndTime;
        // EndTime = DateTime.Now;
        // System.Console.WriteLine("{0}", EndTime - StartTime);
    }
}