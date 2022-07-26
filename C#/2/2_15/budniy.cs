Console.WriteLine("Напишите программу, которая принимает на вход цифру, обозначающую день недели, и проверяет, является ли этот день выходным.");

void day() {
    int day = Convert.ToInt32(Console.ReadLine());
    switch (day) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        Console.WriteLine("будний день");
        break;
        case 6:
        case 7:
        Console.WriteLine("выходной день");
        break;
        default:
        Console.WriteLine("попробуй еще");
        break;
    }
}

day();