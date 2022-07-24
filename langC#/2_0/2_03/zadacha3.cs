Console.WriteLine("Напишите программу, которая принимает на вход число и проверяет, кратно ли оно одновременно 7 и 23.");

void input() {
    Console.Write("введите число: ");
    int number1 = Convert.ToInt32(Console.ReadLine());
    if ((number1 % 7 == 0) && (number1 % 23 == 0)) {
        Console.Write("число делятся на 7 и на 23");
    }
}

input();