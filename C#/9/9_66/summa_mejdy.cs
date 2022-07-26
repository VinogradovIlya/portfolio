Console.WriteLine("Задайте значения M и N. Напишите программу, которая найдёт сумму натуральных элементов в промежутке от M до N.");

Console.Write("введите M: ");
int m = Convert.ToInt32(Console.ReadLine());
Console.Write("введите N: ");
int n = Convert.ToInt32(Console.ReadLine());
Nature(m, n);
Console.Write(Nature(m, n));


int Nature(int m, int n) {
    if (m <= n) {
    return Nature(m, n - 1) + n;
    }
    return 0;
}