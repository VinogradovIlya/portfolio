Console.WriteLine("Напишите программу, которая по заданному номеру четверти, показывает диапазон возможных координат точек в этой четверти (x и y).");

Console.Write("введите четверть: ");
int vvod = Convert.ToInt32(Console.ReadLine());
Chetverti(vvod);

void Chetverti(int vvod) {
    if (vvod > 0 && vvod < 5) {
        if (vvod == 1) Console.Write("x > 0 и y > 0");
        if (vvod == 2) Console.Write("x < 0 и y > 0");
        if (vvod == 3) Console.Write("x < 0 и y < 0");
        if (vvod == 4) Console.Write("x > 0 и y < 0");
    } else {
        Console.Write("error");
    }
}
