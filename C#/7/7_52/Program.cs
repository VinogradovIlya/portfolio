Console.WriteLine("Задайте двумерный массив из целых чисел. Найдите среднее арифметическое элементов в каждом столбце.");

Console.Write("введите m: ");
int m = Convert.ToInt32(Console.ReadLine());
Console.Write("введите n: ");
int n = Convert.ToInt32(Console.ReadLine());
int[,] newArray = new int[m,n];

Show2dArray(
    CreateRandom2dArray(newArray, -100, 100));
Console.WriteLine();

int[,] CreateRandom2dArray(int[,] newArray, int minValue, int maxValue) {
    for (int i = 0; i < newArray.GetLength(0); i++) {
        for (int j = 0; j < newArray.GetLength(1); j++) {
            newArray[i,j] = new Random().Next(minValue, maxValue + 1);
        }
    }
    return newArray;
}

void Show2dArray(int[,] newArray) {
    for (int i = 0; i < newArray.GetLength(0); i++) {
        for (int j = 0; j < newArray.GetLength(1); j++) {
            Console.Write(newArray[i,j] + " ");
        }
        Console.WriteLine();
    }
}

SummaStroki(newArray);
 SummaStolba(newArray);

void SummaStroki(int[,] newArray) {
    for (int i = 0; i < newArray.GetLength(1); i++) {
        int chislo = 0;
        for (int j = 0; j < newArray.GetLength(0); j++) {
            chislo += newArray[i, j];
        }
    Console.Write("{0} ", chislo);
    Console.WriteLine();
    }
    Console.WriteLine();
}

void SummaStolba(int[,] newArray) {
    for (int i = 0; i < newArray.GetLength(0); i++) {
        int chislo = 0;
        for (int j = 0; j < newArray.GetLength(1); j++) {
            chislo += newArray[j,i];
        }
    Console.Write("{0} ", chislo);
    Console.WriteLine();
    }
    Console.WriteLine();
}