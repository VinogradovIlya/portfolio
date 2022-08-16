Console.WriteLine("Напишите программу, которая принимает на вход число (А) и выдаёт сумму чисел от 1 до А.");

Console.Write("введите число (А): ");
int vvod = Convert.ToInt32(Console.ReadLine());
Summa(vvod);
Console.WriteLine(Summa(vvod));

double Summa(int vvod) {
    if (vvod == 1) return 1;
    else return vvod + Summa(vvod - 1);
}
