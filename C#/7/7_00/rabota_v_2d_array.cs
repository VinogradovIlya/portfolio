Console.WriteLine("Задайте двумерный массив размером m×n, заполненный случайными целыми числами.");

Console.WriteLine("введите m: ");
int m = Convert.ToInt32(Console.ReadLine());
Console.WriteLine("введите n: ");
int n = Convert.ToInt32(Console.ReadLine());

Show2dArray(CreateRandom2dArray(m, n, 0, 100));

int[,] CreateRandom2dArray(int m, int n, int minValue, int maxValue) {
    int[,] newArray = new int[m,n];
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
