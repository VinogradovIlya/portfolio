Console.WriteLine("Задайте значения M и N. Напишите программу, которая выведет все натуральные числа в промежутке от M до N..");
Console.Write("введите M: ");
int m = Convert.ToInt32(Console.ReadLine());
Console.Write("введите N: ");
int n = Convert.ToInt32(Console.ReadLine());
Nature(m, n);

void Nature(int m, int n) {
    // if (chislo < M || chislo > N) {
    if (m < n) {
        Nature(m, n - 1);
    }
    Console.Write("{0} ", n);
 }