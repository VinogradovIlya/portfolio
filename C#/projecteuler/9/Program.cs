using System;
using System.Collections.Generic;

/**
https://projecteuler.net/problem=35

Число 197 называется простым круговым числом, потому что все обороты цифр:
197, 971 и 719 сами по себе являются простыми.

Таких простых чисел меньше 100 тринадцать:
2, 3, 5, 7, 11, 13, 17, 31, 37, 71, 73, 79 и 97.

Сколько круговых простых чисел меньше одного миллиона?
*/


class Program
{
    static void Main()
    {
        int task = 1_00;//0_000;

        List<int> circles = new List<int>();
        void NewTurn(int number)  // 197 -> 7*100 + 19 == 719 -> 9*100 + 71 == 971 -> 1*100 + 97 == 197
        {
            int count = number;
            while (count != 0)
            {
            int temp = number % 10; 
            temp *= 100;
            number /= 10;
            number += temp;
            circles.Add(number);
            count /= 10;
            }
        }

        bool PrimeNumber(int number)
        {
            if (number == 2 || number == 3) return true;
            for (int i = 2; i < number; i++)
            {
                if (number % i == 0) return false;
            }
            return true;
        }

        for (int i = 2; i < task; i++)
        {
            if (PrimeNumber(i)) NewTurn(i);
        }
    }
}