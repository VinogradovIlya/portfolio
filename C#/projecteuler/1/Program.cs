using System.Collections.Generic;


/**
https://projecteuler.net/problem=1

Если мы перечислим все натуральные числа до 10, кратные 3 или 5, мы получим 3, 5, 6 и 9.
Сумма этих кратных равна 23.

Найдите сумму всех чисел, кратных 3 или 5 меньше 1000.
*/

class Program
{
    static void Main(string[] args)
    {
        int testNumber = 1000;

        //список для подходящих чисел
        List<int> sum = new List<int>();

        // поиск подходящих чисел
        for (int i = 1; i < testNumber; i++)
        {
            if (i % 3 == 0 || i % 5 == 0) sum.Add(i);
        }

        // поиск суммы
        int result = 0;
        foreach (var item in sum)
        {
            result += item;
        }

        // ответ
        System.Console.WriteLine("{0}", result);
    }
}