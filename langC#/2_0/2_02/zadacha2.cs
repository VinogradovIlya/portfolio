Console.WriteLine("Напишите программу, которая будет принимать на вход два числа и выводить, является ли второе число кратным первому. Если второе число не кратно числу первому, то программа выводит остаток от деления.");

void input() {
    Console.WriteLine("введите два числа");
    int number1 = Convert.ToInt32(Console.ReadLine());
    int number2 = Convert.ToInt32(Console.ReadLine());
    if (number2 % number1 == 0) {
        Console.WriteLine("второе кратно первому");
    } else {
        Console.WriteLine("второе не кратно первому");
    }
}

input();