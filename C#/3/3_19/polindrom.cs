Console.WriteLine("Напишите программу, которая принимает на вход пятизначное число и проверяет, является ли оно палиндромом.");

Console.Write("Введите пятизначное число: ");
int vvod = Convert.ToInt32(Console.ReadLine());
int first = vvod / 10000;
int second = (vvod / 1000) - (first * 10);
int fourth = ((vvod % 100) - (vvod % 10)) / 10;
int fifth = vvod % 10;

Chisla(vvod);
Polindrom(first, second, fourth, fifth);

void Chisla(int vvod) { // как реализовать переход интов из этого метода в другой? Если закомитить строки 5 - 8, будет ошибка
    int first = vvod / 10000;
    int second = (vvod / 1000) - (first * 10);
    int fourth = ((vvod % 100) - (vvod % 10)) / 10;
    int fifth = vvod % 10;
}

void Polindrom(int first, int second, int fourth, int fifth) {
    if (first == fifth && second == fourth) Console.Write("число полиндром");
    else Console.Write("число не полиндром");
}