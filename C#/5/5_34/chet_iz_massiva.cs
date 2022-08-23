Console.WriteLine("Задайте массив заполненный случайными положительными трёхзначными числами. Напишите программу, которая покажет количество чётных чисел в массиве.");
int[] array = new int[10];

/* два метода: 
первый создает массив*/
MethodArrayOne(array);
ShowArray(array);
Console.WriteLine();
// второй: считает четные числа
MethodArrayTwo(array);
Console.WriteLine("{0}", MethodArrayTwo(array));

int[] MethodArrayOne(int[] array) {
    for (int i = 0; i < 10; i++) {
        array[i] = new Random().Next(100, 1000);
    }
    return array;
}

void ShowArray(int[] array) {
    for (int i = 0; i < array.Length; i++) {
        Console.Write(array[i] + " ");
    }
}

int MethodArrayTwo(int[] array) {
    int count = 0;
    for (int i = 0; i < array.Length; i++) {
        int chet = array[i] % 2;
        if (chet == 0) count++;
    }
    return count;
}