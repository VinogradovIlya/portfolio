Console.WriteLine("Напишите программу, которая принимает на вход пятизначное число и проверяет, является ли оно палиндромом.");

Console.Write("Введите содержимое массива: ");
string vvod = Console.ReadLine();
Polindrom(vvod);

void Polindrom(string vvod) {
    string[] symbol = new string[5];
    if (string[0] && string[1] == string[3] && string[4]) {
        Console.Write("число -- полиндром");
    } else {
        Console.Write("число -- не полиндром");
    }
}