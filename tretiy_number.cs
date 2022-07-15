Console.WriteLine("Напишите программу, которая выводит третью цифру заданного (максимум 5 знаков) числа или сообщает, что третьей цифры нет.");

int zadacha() {
    Console.WriteLine("введите число: ");
    int chislo = Convert.ToInt32(Console.ReadLine());
    int result;
    if (chislo < 100) { // проверка есть ли третий знак
        Console.Write("третьей цифры нет");
    } result = chislo % 10;
    if (chislo < 1000 && chislo > 100) { // третий знак
        result = chislo % 10;
    }
    if (chislo < 10000 && chislo > 1000) { // 3/4
        result = (chislo % 100 - chislo % 10) / 10;
    }
    if (chislo < 100000 && chislo > 10000) { // 3/5
        result = (chislo % 1000 - chislo % 100) / 100;
    } else {
        Console.WriteLine("молодец держи"); // 3/6
        if (chislo < 1000000 && chislo > 100000) {
        result = (chislo % 10000 - chislo % 1000) / 1000;
        }
    }
    return result;
}

Console.Write(zadacha());