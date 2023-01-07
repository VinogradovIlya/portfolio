using System;
using System.Math;

/**
https://projecteuler.net/problem=6

Сумма квадратов первых десяти натуральных чисел равна
1^2 + 2^2 + 3^2 + ... + 10^2 == 385
Квадрат суммы первых десяти натуральных чисел равен,
(1+2+3+...+10) == 55^2 == 3025
Следовательно, разница между суммой квадратов первых десяти натуральных чисел и квадратом суммы равна
3025 - 385 == 2640
Найдите разницу между суммой квадратов первых ста натуральных чисел и квадратом суммы.
*/

class Program
{
    static void Main(string[] args)
    {
        //старт
        int number = 100;

        // считаю сумму квадратов
        int SumSquare(int number)
        {
            int sumSquare = 0;
            for (int i = 1; i <= number; i++)
            {
                sumSquare += (int)Math.Pow(i, 2);
            }
            return sumSquare;
        }

        // считаю квадрат суммы
        int SquareSum(int number)
        {
            int sum = 0;
            for (int i = 1; i <= number; i++)
            {
                sum += i;
            }
            sum = (int)Math.Pow(sum, 2);
            return sum;
        }

        // ответ
        System.Console.WriteLine(
            "{0}", SquareSum(number) - SumSquare(number));
    }
}