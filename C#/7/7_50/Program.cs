Console.WriteLine("Напишите программу, которая на вход принимает позиции элемента в двумерном массиве, и возвращает значение этого элемента или же указание, что такого элемента нет.");

Console.Write("выберите первую координату из массива 10*10: ");
// string[] koordinata = Console.ReadLine().Split(new Char[] { ' ' });
int koordinata1 = Convert.ToInt32(Console.ReadLine());
Console.Write("выберите вторую координату из массива 10*10: ");
int koordinata2 = Convert.ToInt32(Console.ReadLine());

double[,] newArray = new double[10,10];

if (koordinata1 > 10 || koordinata2 > 10) Console.WriteLine("no");
else { 
    CreateRandom2dArray(newArray, -10, 10);
    Console.WriteLine("{0}", newArray[koordinata1,koordinata2]);
}

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

// void Show2dArray(double[,] array) {
//     for (int i = 0; i < array.GetLength(0); i++) {
//         for (int j = 0; j < array.GetLength(1); j++) {
//             Console.Write(array[i,j] + " ");
//         }
//         Console.WriteLine();
//     }
// }