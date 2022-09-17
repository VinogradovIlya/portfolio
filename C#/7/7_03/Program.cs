Console.WriteLine("Задайте двумерный массив. Найдите сумму элементов, находящихся на главной диагонали (с индексами (0,0); (1;1) и т.д.");

Console.Write("введите m: ");
int m = Convert.ToInt32(Console.ReadLine());
Console.Write("введите n: ");
int n = Convert.ToInt32(Console.ReadLine());

int[,] newArray = new int[m,n];

Show2dArray(
    CreateRandom2dArray(newArray, 0, 10));
Console.WriteLine();

Console.WriteLine("{0}", Diagonal(newArray));

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

int Diagonal(int[,] newArray) {
    int i, j;
    int summ = 0;
    for (i = 0; i < newArray.GetLength(0); i++) {
        for (j = 0; j < newArray.GetLength(1); j++) {
            if (i == j) summ += newArray[i,j];
        }
    }
    return summ;
}


// весь метод в пяти строчках
// int summ = 0;
// for (int i = 0; i < newArray.GetLength(0); i++) {
// summ += newArray[i,j];
// }
// return summ;