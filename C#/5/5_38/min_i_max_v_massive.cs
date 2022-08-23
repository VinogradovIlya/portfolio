Console.WriteLine("Задайте массив вещественных чисел. Найдите разницу между максимальным и минимальным элементов массива.");

int[] array = new int[10];

/* три метода: 
первый создает массив*/
MethodArrayOne(array);
ShowArray(array);
Console.WriteLine();
// второй: ищет наибольшее/наименьшее число
MethodArrayTwo(array);
Console.WriteLine("{0}", MethodArrayTwo(array));
// третий метод ищет сумму ?

int[] MethodArrayOne(int[] array) {
    for (int i = 0; i < 10; i++) {
        array[i] = new Random().Next(-999, 1000);
    }
    return array;
}

void ShowArray(int[] array) {
    for (int i = 0; i < array.Length; i++) {
        Console.Write(array[i] + " ");
    }
}

double MethodArrayTwo(int[] array) {
    double min, max;
    min = max = 0;
    for (int i = 0; i < array.Length; i++) {
        if (array[i] > max) max = array[i];
        if (array[i] < min) min = array[i];
    }
    return max - min;
}