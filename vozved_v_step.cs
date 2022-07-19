Console.WriteLine("Напишите программу, которая на вход принимает два числа A и B, и возводит число А в целую степень B с помощью рекурсии.");

Console.Write("введите A: ");
int a = Convert.ToInt32(Console.ReadLine());
Console.Write("введите B: ");
int b = Convert.ToInt32(Console.ReadLine());
Stepen(a, b);
Console.Write(Stepen(a, b));

int Stepen(int a, int b) {
    if (b > 0) {
        return Stepen(a, b - 1) * a;
    } 
    return 1;
}