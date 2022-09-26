Console.WriteLine("Задайте двумерный массив. Напишите программу, которая поменяет местами первую и последнюю строку массива.");

Console.Write("введите m: ");
int m = Convert.ToInt32(Console.ReadLine());
Console.Write("введите n: ");
int n = Convert.ToInt32(Console.ReadLine());
int[,] array = new int[m,n];

Show2dArray(
    CreateRandom2dArray(array, -100, 100));
Console.WriteLine();

int[,] CreateRandom2dArray(int[,] array, int minValue, int maxValue) {
    for (int i = 0; i < array.GetLength(0); i++) {
        for (int j = 0; j < array.GetLength(1); j++) {
            array[i,j] = new Random().Next(minValue, maxValue + 1);
        }
    }
    return array;
}

void Show2dArray(int[,] array) {
    for (int i = 0; i < array.GetLength(0); i++) {
        for (int j = 0; j < array.GetLength(1); j++) {
            Console.Write(array[i,j] + " ");
        }
        Console.WriteLine();
    }
}

Show2dArray(
    StringReplace(array));

int[,] StringReplace(int[,] array) {
    for (int i = 0; i < array.GetLength(0); i++) {
        for (int j = 0; j < array.GetLength(1); j++) {
            if (i == array.GetLength(0)) {
            }
        }
    }
    return array;
}