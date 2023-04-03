using System;
using System.Text;

class Program
{
    static void Main(string[] args)
    {
        int days = System.Convert.ToInt32(System.Console.ReadLine());
        string[] paintings = System.Console.ReadLine().Split();

        int[] contrasts = new int[days];
        for (int i = 0; i < days; i++)
        {
            contrasts[i] = System.Convert.ToInt32(paintings[i]);
        }

        int max = contrasts[0] - contrasts[1];
        int temp;
        int maxDays = 0;
        StringBuilder sb = new StringBuilder();

        for (int i = 0; i < days; i++)
        {
            for (int j = 0; j < days; j++)
            {
                temp = contrasts[i] - contrasts[j];
                if (max <= temp)
                {
                    max = temp;
                    if (i - j > maxDays)
                    {
                        maxDays = i - j;
                        sb.Clear();
                        sb.Append(i+1);
                        sb.Append(" ");
                        sb.Append(j+1);
                    }
                    if (j - i > maxDays)
                    {
                        maxDays = j - i;
                        sb.Clear();
                        sb.Append(j+1);
                        sb.Append(" ");
                        sb.Append(i+1);
                    }
                }
            }
        }
        System.Console.WriteLine(sb);
    }
}