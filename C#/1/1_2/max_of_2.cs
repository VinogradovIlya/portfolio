Console.WriteLine("<максимум из двух чисел>");
Console.Write("введите 1 число: ");
int a = Convert.ToInt32(Console.ReadLine());
Console.Write("введите 2 число: ");
int b = Convert.ToInt32(Console.ReadLine());
Console.Write("наибольшее число -- ");
if (a > b) Console.WriteLine("{0}", a);
if (a < b) Console.WriteLine("{0}", b);