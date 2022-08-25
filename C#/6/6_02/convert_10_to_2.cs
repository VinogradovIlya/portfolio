Console.WriteLine("Напишите программу, которая будет преобразовывать десятичное число в двоичное.");

Console.WriteLine("введите число: ");
int amount = Convert.ToInt32(Console.ReadLine());


Console.WriteLine(ConvertNumber(amount));


string ConvertNumber(int amount) {
    string count = string.Empty;
    while (amount > 0) {
        count = amount % 2 + count;
        amount = amount / 2;
    }
    return count;
}

