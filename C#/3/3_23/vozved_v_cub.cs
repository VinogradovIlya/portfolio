Console.WriteLine("Напишите программу, которая принимает на вход число (N) и выдаёт таблицу кубов чисел от 1 до N.");

Console.Write("введите число (N): ");
int n = Convert.ToInt32(Console.ReadLine());

Cub(n);

void Cub(int n) {
    for (int count = 1; count <= n; count++) {
        int cub = count * count * count;
        Console.Write("{0} ", cub);
    }
}