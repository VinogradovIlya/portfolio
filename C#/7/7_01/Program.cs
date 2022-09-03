Console.WriteLine("Задайте двумерный массив размера m на n, каждый элемент в массиве находится по формуле: Aij = I + j. Выведите полученный массив на экран.");

int[,] CreateRandom2dArray(int m, int n) {
    int[,] newArray = new int[m,n];
    int i, j;
    for (i = 0; i < newArray.GetLength(0); i++) {
        for (j = 0; j < newArray.GetLength(1); j++) {
            newArray[i,j] = i + j;
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

Console.WriteLine("введите m: ");
int m = Convert.ToInt32(Console.ReadLine());
Console.WriteLine("введите n: ");
int n = Convert.ToInt32(Console.ReadLine());

int[,] myArray = CreateRandom2dArray(m, n);
Show2dArray(myArray);