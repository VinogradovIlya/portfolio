Console.WriteLine("Напишите программу, которая принимает на вход трёхзначное число и на выходе показывает вторую цифру этого числа.");

void zadacha() {
    Console.WriteLine("введите трехзначное число ");
    int chislo = Convert.ToInt32(Console.ReadLine());
    if (chislo < 100 || chislo > 999) {
        Console.Write("по условию нужно трехзначное...");
        } else {
            Console.WriteLine("число: " + chislo);
            int step1 = chislo / 10;
            int step2 = step1 % 10;
            Console.WriteLine($"вторая цифра: {step2}");
        }
}

zadacha();