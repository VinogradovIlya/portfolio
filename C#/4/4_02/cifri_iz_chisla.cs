Console.WriteLine("Напишите программу, которая принимает на вход число и выдаёт количество цифр в числе.");

Console.Write("введите число: ");
string chislo = Console.ReadLine();
int number = Convert.ToInt32(chislo);

int Dlina(string chislo) {
    int length = chislo.Length;
    return length;
}

int Cifra(int number) {
    int count = 0;
    do {
        number = number / 10;
        count++;
    } while (number != 0);
    // while (number != 0) {
    //     number = number / 10;
    //     count++;
    // }
    return count;
}

Console.WriteLine(Dlina(chislo));
Console.WriteLine();
Console.WriteLine(Cifra(number));