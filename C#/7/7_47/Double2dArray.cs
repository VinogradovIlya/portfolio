Console.WriteLine("Задайте двумерный массив размером m×n, заполненный случайными вещественными числами.");

Console.Write("введите m: ");
int m = Convert.ToInt32(Console.ReadLine());
Console.Write("введите n: ");
int n = Convert.ToInt32(Console.ReadLine());

double[,] newArray = new double[m,n];

Show2dArray(
    CreateRandom2dArray(newArray, -10, 10));
Console.WriteLine();

double[,] CreateRandom2dArray(double[,] newArray, int minValue, int maxValue) {
    Random rnd = new Random();
    for (int i = 0; i < newArray.GetLength(0); i++) {
        for (int j = 0; j < newArray.GetLength(1); j++) {
            newArray[i,j] = new Random().Next(minValue, maxValue + 1);
            double chislo = rnd.NextDouble();
            newArray[i,j] += chislo; // как округлить до двух знаков?
            newArray[i,j] = Math.Round(newArray[i,j], 2); // округление до любого количества знаков!
        }
    }
    return newArray;
}

void Show2dArray(double[,] array) {
    for (int i = 0; i < array.GetLength(0); i++) {
        for (int j = 0; j < array.GetLength(1); j++) {
            Console.Write(array[i,j] + " ");
        }
        Console.WriteLine();
    }
}