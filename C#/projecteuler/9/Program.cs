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
        int task = 1_000_000;
        
        // список простых чисел
        List<int> primeNumber = new List<int>();
        for (int i = 2; i < task; i++)
        {
            if (PrimeNumber(i) == true) primeNumber.Add(i);
        }

        // прохожусь по простым числам, кручу их и проверяю на простоту
        List<string> result = new List<string>();
        foreach (var item in primeNumber)
        {
            if (PrimeNumber(NewTurn(item)) == true) result.Add(NewTurn(item));
        }

        // ответ
        System.Console.WriteLine(result.Count());
        
    }        
    static bool PrimeNumber(int number)
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
    
    static bool PrimeNumber(string number)
    {
        string[] numbers = number.Split();
        for (int i = 0; i < numbers.Length; i++)
        {
            int num = Convert.ToInt32(numbers[i]);
            if (PrimeNumber(num) == false) return false;
        }
        return true;
    }

    static string NewTurn(int number)
    {
        if (Digit(number) == 1) return System.Convert.ToString(number);

        int stepTest = number;
        string rst = Convert.ToString(number);
        for (int i = 1; i < Digit(number); i++)
        {

            // получение нового числа
            int temp = stepTest % 10;
            int temp1 = stepTest / 10;
            string step1 = string.Empty;
            step1 = Convert.ToString(temp) + Convert.ToString(temp1);
            int result = Convert.ToInt32(step1);    

            rst = rst + " " + result;

            stepTest = result;
        }
        return rst;
    }

    static int Digit(int number)
    {
        int count = 0;
        while (number > 0)
        {
            number /= 10;
            count++;
        }
        return count;
    }
}