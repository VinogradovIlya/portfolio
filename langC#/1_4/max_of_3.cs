Console.WriteLine("<максимум из двух чисел>");
Console.Write("введите 1 число: ");
int a = Convert.ToInt32(Console.ReadLine());
Console.Write("введите 2 число: ");
int b = Convert.ToInt32(Console.ReadLine());
Console.Write("введите 3 число: ");
int c = Convert.ToInt32(Console.ReadLine());
Console.Write("наибольшее число -- ");
int max;
if (a > b) {
    max = a;
} else {
    max = b;
}
if (max < c) {
    max = c;
}
Console.WriteLine("{0}", max);