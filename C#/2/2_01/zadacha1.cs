Console.WriteLine("Напишите программу, которая выводит случайное трёхзначное число и удаляет вторую цифру этого числа.");

int znach() {
    int rand = new Random().Next(100, 1000);
    Console.WriteLine("число: " + rand);
    int first = rand / 100;
    int last = rand % 10;
    int finish = first * 10 + last;
    return finish;
}

Console.Write("{0}", znach()); //метод который можно вызывать