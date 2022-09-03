Console.WriteLine("Задайте двумерный массив. Найдите элементы, у которых оба индекса чётные, и замените эти элементы на их квадраты.");

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

int[,] SquareArray(int[,] array) {
    int[,] newArray = new int[m,n];
    for (int i = 0; i < array.GetLength(0); i++) {
        i++;
        for (int j = 0; j < array.GetLength(1); j++) {
            j++;
            array[i,j] = array[i,j] * array[i,j];
        }
    }
    return array;
}

Console.Write("введите m: ");
int m = Convert.ToInt32(Console.ReadLine());
Console.Write("введите n: ");
int n = Convert.ToInt32(Console.ReadLine());

int[,] myArray = CreateRandom2dArray(newArray, -10, 10);
Console.WriteLine();
Show2dArray(myArray);
Console.WriteLine();
int[,] finalArray = SquareArray(newArray);
Show2dArray(finalArray);