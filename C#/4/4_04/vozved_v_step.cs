Console.WriteLine("Напишите цикл, который принимает на вход два числа (A и B) и возводит число A в натуральную степень B.");

Console.Write("введите число A: ");
int a = Convert.ToInt32(Console.ReadLine());
Console.Write("введите число B: ");
int b = Convert.ToInt32(Console.ReadLine());
Console.WriteLine(Stepeni(a, b));

int Stepeni(int a, int b) {
    int result = 1;
    for (int count = 1; count <= b; count++) {
        result = result * a;
    }
    return result;
}
