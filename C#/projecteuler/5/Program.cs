using System;
using System.Collections.Generic;

/**
https://projecteuler.net/problem=14

Для множества положительных целых чисел определена следующая итерационная последовательность:
для четного n: n/2
для нечетного n: 3n + 1
Используя приведенное выше правило и начиная с 13, мы генерируем следующую последовательность:
13 -> 40 -> 20 -> 10 -> 5 -> 16 -> 8 -> 4 -> 2 -> 1
Видно, что эта последовательность (начиная с 13 и заканчивая 1) содержит 10 членов. 
Хотя это еще не доказано (проблема Коллатца), считается, что все начальные числа заканчиваются на 1.
Какое начальное число меньше миллиона дает самую длинную цепочку?
ПРИМЕЧАНИЕ. После того, как цепочка запустится, количество участников может превысить один миллион.
*/

class Program
{
    static void Main()
    {
        ulong NeChet(ulong number)
        {
            number *= 3;
            number++;
            return number;
        }

        ulong Chet(ulong number)
        {
            number /= 2;
            return number;
        }

        int Circles(ulong number)
        {
            int count = 1;
            while (number != 1)
            {
                number = (number % 2 == 0) ? Chet(number) : NeChet(number);
                count++;
            }
            return count;
        }

        // сомнительное решение
        List<string> result = new List<string>(); 
        for (ulong n = 1; n < 1_000_000; n++)
        {
            result.Add(n + " " + Circles(n));
        }

        System.Console.WriteLine($"{result.Max()}");
    }
}
