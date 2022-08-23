Console.WriteLine("Задайте массив из 12 элементов, заполненный случайными числами из промежутка [-9, 9]. Найдите сумму отрицательных и положительных элементов массива.");

int size = 12;
int[] array = new int[size];
int min = -9;
int max = 9;

CreateRandomArray(size, min, max);
ShowArray(array);
Summ(array);

int[] CreateRandomArray(int size, int min, int max) {
    for (int i = 0; i < size; i++) {
        array[i] = new Random().Next(min, max + 1);
    }
    return array;
}


void ShowArray(int[] array) {
    for (int i = 0; i < array.Length; i++) {
        Console.Write(array[i] + " ");
    }
    Console.WriteLine();
}


void Summ(int[] array) {
    int summPositive = 0;
    int summNegative = 0;
    for (int i = 0; i < array.Length; i++) {
        if (array[i] <= 0) {
            summPositive += array[i];
        } else {
            summNegative += array[i];
        }
    }
    Console.WriteLine("{0}", summPositive);
    Console.WriteLine("{0}", summNegative);
}