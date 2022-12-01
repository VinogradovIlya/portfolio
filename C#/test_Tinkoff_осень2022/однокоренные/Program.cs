using System;
using System.Text.RegularExpressions;
 
static class Program
{
    static void Main(string[] args)
    {
        // string[] rows = {"Москва— столица Российской Федерации.",
        //                  "Это предложение оказалось здесь случайно",
        //                  "Москва - город федерального значения, административный центр Центрального федерального округа и центр Московской области.",
        //                  "Жители столицы - москвичи.",
        //                  "Как и это."};
        // foreach (string row in rows)
        // {
        //     if (Regex.IsMatch(row, "моск", RegexOptions.IgnoreCase))
        //         Console.WriteLine(row);
        //     foreach (Match match in Regex.Matches(row, @"\b\w*моск\w*\b", RegexOptions.IgnoreCase))
        //         Console.WriteLine("\t\t{0}", match.Value);
        // }

        List<string> test = new List<string>() {"a", "ab", "abc", "aboba", "d"};
        foreach (string row in test)
        {
            if (Regex.IsMatch(row, "ab", RegexOptions.IgnoreCase))
                Console.WriteLine(row);
            foreach (Match match in Regex.Matches(row, @"\b\w*ab\w*\b", RegexOptions.IgnoreCase))
                Console.WriteLine("\t\t{0}", match.Value);
        }
    }
}
