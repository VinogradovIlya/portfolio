using System;
using System.Text;

/**
https://projecteuler.net/problem=40

Иррациональная десятичная дробь получается путем объединения положительных целых чисел:
0,12345678910 1 112131415161718192021...
Видно, что 12 -я цифра дробной части равна 1.
Если d n представляет собой n -ю цифру дробной части, найдите значение следующего выражения.
d 1 х d 10 х d 100 х d 1000 х d 10000 х d 100000 х d 1000000
*/


class Program
{
    static void Main()
    {
        StringBuilder text = new StringBuilder(Formula(1_000_000));
        // System.Console.WriteLine(Number(text, 1));
        // System.Console.WriteLine(Number(text, 10));
        // System.Console.WriteLine(Number(text, 100));
        // System.Console.WriteLine(Number(text, 1000));
        // System.Console.WriteLine(Number(text, 10000));
        // System.Console.WriteLine(Number(text, 100000));
        // System.Console.WriteLine(Number(text, 1000000));
        int result = 1;
        for (int i = 1; i <= 1_000_000; i *= 10)
        {
            // System.Console.WriteLine(i);
            result *= Number(text, i);
            if (Number(text, i) == 0)
            {
                break;
            }
        }
        // ответ
        System.Console.WriteLine(result);
    }

    static string Formula(int number)
    {
        StringBuilder result = new StringBuilder("0,");
        for (int i = 1; i <= number; i++)
        {
            result.Append(i);
        }
        return result.ToString();
    }

    static int Number(StringBuilder sb, int number)
    {
        string strSB = sb.ToString();
        string[] tempStr = strSB.Split(',');
        char[] arr = tempStr[1].ToCharArray();
        return System.Convert.ToInt32(arr[number-1].ToString());
    }
}
