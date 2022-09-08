Console.WriteLine("Задайте двумерный массив. Найдите элементы, у которых оба индекса чётные, и замените эти элементы на их квадраты.");

Console.Write("введите m: ");
int m = Convert.ToInt32(Console.ReadLine());
Console.Write("введите n: ");
int n = Convert.ToInt32(Console.ReadLine());

int[,] newArray = new int[m,n];

Show2dArray(
    CreateRandom2dArray(newArray, -10, 10));
Console.WriteLine();

Show2dArray(
    SquareArray(newArray));

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

// // работает в шахматном порядке
// int[,] SquareArray(int[,] newArray) {
//     int i, j;
//     for (i = 0; i < newArray.GetLength(0); i++) {
//         for (j = 0; j < newArray.GetLength(1); j++) {
//             if ((i % 2 == 1) || (j % 2 == 1)) newArray[i,j] = newArray[i,j] * newArray[i,j];
//         }
//     }
//     return newArray;
// }

// оба индексы четные
int[,] SquareArray(int[,] newArray) {
    int i, j;
    for (i = 0; i < newArray.GetLength(0); i++) {
        for (j = 0; j < newArray.GetLength(1); j++) {
            if ((i % 2 == 0) && (j % 2 == 0)) newArray[i,j] = newArray[i,j] * newArray[i,j];
        }
    }
    return newArray;
}