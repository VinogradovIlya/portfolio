Console.WriteLine("Напишите программу, которая принимает на вход число и выдаёт сумму цифр в числе.");

//ввод
Console.Write("введите число: ");
int number = Convert.ToInt32(Console.ReadLine());

SummNumber(number);
Console.WriteLine("{0}", SummNumber(number));

int SummNumber(int number) {
    int summ = 0;
    while (number != 0) {
        int num = number % 10;
        summ += num;
        number = number / 10;
    }
    return Math.Abs(summ);
}