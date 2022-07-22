Console.WriteLine("Задайте значение N. Напишите программу, которая найдет факториал числа N рекурсивным методом.");

Console.Write("введите N: ");
int vvod = Convert.ToInt32(Console.ReadLine());
Factorial(vvod);
Console.Write(Factorial(vvod));


int Factorial(int vvod) {
    if (vvod > 0) {
        //Factorial(vvod - 1) * vvod;
        return Factorial(vvod - 1) * vvod;
    }
    return 1;
}
// почему при вводе Н более 32 вылазит абра кадабра?(