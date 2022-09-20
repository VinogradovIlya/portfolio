Console.WriteLine("Задайте двумерный массив размером m×n, заполненный случайными целыми числами.");

Console.Write("введите m: ");
int m = Convert.ToInt32(Console.ReadLine());
Console.Write("введите n: ");
int n = Convert.ToInt32(Console.ReadLine());
int[,] newArray = new int[m,n];

Show2dArray(
    CreateRandom2dArray(newArray, -100, 100));

int[,] CreateRandom2dArray(int[,] newArray, int minValue, int maxValue) {
    for (int i = 0; i < newArray.GetLength(0); i++) {
        for (int j = 0; j < newArray.GetLength(1); j++) {
            newArray[i,j] = new Random().Next(minValue, maxValue + 1);
        }
    }
    return newArray;
}

void Show2dArray(int[,] array) {
    for (int i = 0; i < array.GetLength(0); i++) {
        for (int j = 0; j < array.GetLength(1); j++) {
            Console.Write(array[i,j] + " ");
        }
        Console.WriteLine();
    }
}
