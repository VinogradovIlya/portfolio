Console.WriteLine("Напишите программу, которая будет преобразовывать десятичное число в двоичное.");

Console.WriteLine("введите число: ");
string number = String.Empty;
number = Console.ReadLine();
int amount = Convert.ToInt32(number);

ConvertTo(amount, number);
Console.WriteLine("{0}", ConvertTo(amount, number));

int ConvertTo(int amount, string number) {
    int count = 0;
    for (int i = 0; i < number.Length; i++) {
        count = amount % 2;
        Console.WriteLine("{0}", count);
        return count;
    }
    return count;
}