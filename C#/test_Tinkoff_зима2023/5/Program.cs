using System;
using System.Collections.Generic;

internal class Program
{
    private static void Main(string[] args)
    {
        string[] inputNM = System.Console.ReadLine().Split();
        int n = System.Convert.ToInt32(inputNM[0]);
        int m = System.Convert.ToInt32(inputNM[1]);

        List<string> input = new List<string>(m);
        for (int i = 0; i < m; i++)
        {
            input.Add(System.Console.ReadLine());
        }
        input.Sort();
        System.Console.WriteLine();
        foreach (string item in input)
        {
            System.Console.WriteLine(item);
        }

        // построение подходящего маршрута
        List<string> path = new List<string>(m);
        for (int i = 1; i < m; i += 2)
        {
            string[] start = input[i - 1].Split();
            int number1 = System.Convert.ToInt32(start[0]);
            int number2 = System.Convert.ToInt32(start[1]);
            int number3 = System.Convert.ToInt32(start[2]);

            string[] finish = input[i].Split();
            int number11 = System.Convert.ToInt32(finish[0]);
            int number21 = System.Convert.ToInt32(finish[1]);
            int number31 = System.Convert.ToInt32(finish[2]);

            if (number2 <= number21 && number11 == number2) path.Add(input[i - 1]);
        }

        foreach (string item in path)
        {
            System.Console.WriteLine(item);
        }
    }
}

// ответы
// System.Console.WriteLine(!!!!.Count);

/**************
работает при четном m
*/
