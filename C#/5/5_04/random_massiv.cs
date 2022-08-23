Console.WriteLine("Задайте одномерный массив из 20 случайных чисел. Найдите количество элементов массива, значения которых лежат в отрезке [10,99].");
Console.WriteLine();

int[] array = new int[20];
/* два метода:
первый -- создание массива*/
MetodArrayOne();
ShowArray(array);
//второй -- счетчик значений
Console.WriteLine();
MetodArrayTwo(array);


int[] MetodArrayOne() {
    // Random rnd = new Random();
    for (int i = 0; i < array.Length; i++) {
        //array[i] = rnd.Next();
        array[i] = new Random().Next(-1000, 1001);
    }
    return array;
}


void MetodArrayTwo(int[] array) {
    for (int i = 0; i < array.Length; i++) {
        if (array[i] > 10 && array[i] < 100) Console.Write(array[i] + " ");
    }
}


void ShowArray(int[] array) {
    for (int i = 0; i < array.Length; i++) {
        Console.Write(array[i] + " ");
    }
    Console.WriteLine();
}
