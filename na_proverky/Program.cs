Console.WriteLine("Напишите программу, которая принимает на вход число (N) и выдаёт квадраты чисел от 1 до N.");

Console.Write("введите число N: ");
int vvod = Convert.ToInt32(Console.ReadLine());
Codered(vvod);
//Console.Write($"{Codered(vvod)}");

// int Codered(int vvod) {
//     if (vvod > 0) {
//         return Codered(vvod - 1) * vvod;
//     } else {
//         return 0;
//     }
// }

//вопрос: я пишу код такой структуры на С# (рекурсия, иф(условие), далее return что-то там и return 0) проблема в том, что уже не в первый раз программа не выходит через рекурсию, а идет через return 0. Почему так и где я не прав?

void Codered(int vvod) {
    for (int i = 1; i < vvod; i++) {
        int square = i * i;
        Console.Write("{0} ", square);
    }
    Console.Write("{0}", vvod);
}