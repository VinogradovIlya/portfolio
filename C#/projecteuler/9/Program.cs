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
        int task = 1_000;//_000;
        
        bool PrimeNumber(int number)
        {
            if (number == 2 || number == 3) return true;
            else 
            {
                for (int i = 2; i < number; i++)
                {
                    if (number % i == 0) return false;
                }
                return true;
            }
            
        }

        List<int> primeNumber = new List<int>();
        for (int i = 2; i < task; i++)
        {
            if (PrimeNumber(i) == true) primeNumber.Add(i);
        }

        int NewTurn(int number)
        {
            List<int> recurs = new List<int>();

            if (number < 10) return number;
            else
            {
                int temp = number % 10;
                int temp1 = number / 10;
                string step1 = string.Empty;
                step1 = Convert.ToString(temp) + Convert.ToString(temp1);
                int result = Convert.ToInt32(step1);    
                return result;
            }
        
        }

        int Digit(int number)
        {
            int count = 0;
            while (number > 0)
            {
                number /= 10;
                count++;
            }
            return count;
        }

        // List<int> variants = new List<int>();
        foreach (var item in primeNumber)
        {
            int count = Digit(item);
            int value = item;
        
            if (count > 1) {
                for (int i = 0; i < count; i++)
                {
                    int step1 = NewTurn(value);
                    value = step1;
                    System.Console.WriteLine(value);
                }
            }

        }


    }
}