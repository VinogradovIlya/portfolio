using System;

internal partial class Program
{
    private static void Main(string[] args)
    {
        int n = System.Convert.ToInt32(System.Console.ReadLine());
        string[] s = System.Console.ReadLine().Split();
        string b = System.Console.ReadLine();

        int count = 0; // счетчик слов

        for (int i = 0; i < s.Length; i++)
        { //прохожу по словам
            int lengthWord = s[i].Length;// длина слова
            char[] symbols = b.ToCharArray(); // заданная поклеточная раскраска

            int j = lengthWord * i; // поправочный коэффициент;
            while (j < n - 1)
            { // прохожу посимвольно по одному слову
                j++;
                if (symbols[j] == symbols[j - 1])
                {
                    count++;
                    break;
                }
            }

        }
        System.Console.WriteLine($"{count}");
    }
}