using System;
using System.Collections.Generic;
using System.Linq;


internal partial class Program
{
    private static void Main(string[] args)
    {
        int a, b;
        int n = Convert.ToInt32(Console.ReadLine());

        List<int> delA = new List<int>();
        List<int> delB = new List<int>();
        List<string> result = new List<string>();

        // nok(a, b) = a * b / nod
        int nok = 0;
        int nod;

        for (a = 1; a < n; a++)
        {
            b = n - a;
            Od(a, b);
            nod = 0;
            Nod(delA, delB);
            Nok(a, b, nod, result);

            delA.Clear();
            delB.Clear();
        }

        void Od(int a, int b)
        {
            for (int i = 1; i <= a; i++)
            {
                if (a % i == 0) delA.Add(i);
            }

            for (int i = 1; i <= b; i++)
            {
                if (b % i == 0) delB.Add(i);
            }
        }

        int Nod(List<int> delA, List<int> delB)
        {
            int sizeA = delA.Count() - 1;
            int sizeB = delB.Count() - 1;
            for (int i = sizeA; i >= 0; i--)
            {
                for (int j = sizeB; j >= 0; j--)
                {
                    if (delA[i] == delB[j]) return nod = delA[i];
                }
            }
            return nod;
        }

        int Nok(int a, int b, int nod, List<string> result)
        {
            nok = a * b / nod;
            string finalString = a + " " + b + " " + nok;
            result.Add(finalString);
            return nok;
        }

        string[] res = result.ToArray();
        string finish = string.Empty;
        AB(res, finish);
        void AB(string[] res, string finish)
        {
            string[] one = res[0].Split();
            int ab = Convert.ToInt32(one[2]);
            for (int i = 1; i < res.Length; i++)
            {
                string[] step1 = res[i].Split();
                int step2 = Convert.ToInt32(step1[2]);
                if (ab >= step2)
                {
                    ab = step2;
                    finish = step1[0] + " " + step1[1];
                }
            }
            System.Console.WriteLine(finish);
        }
    }
}