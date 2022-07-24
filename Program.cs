Console.WriteLine("Напишите программу, которая принимает на вход число (N) и выдаёт квадраты чисел от 1 до N.");

Console.Write("введите число N: ");
int vvod = Convert.ToInt32(Console.ReadLine());
Codered(vvod);
Console.Write($"{Codered(vvod)}");

int Codered(int vvod) {
    if (vvod > 0) {
        return Codered(vvod - 1) * vvod;
    } else {
        return 0;
    }
}

//вопрос: я не впервый раз код такой структуры (рекурсия, иф(условие), далее return что-то там и опять ретерн) проблема в том, что уже не в первый раз программа не выходит через рекурсию, а идет через return 0. Почему так и где я не прав?