Console.WriteLine("Задайте массив вещественных чисел. Найдите разницу между максимальным и минимальным элементов массива.");

double[] array = new double[10];

/* три метода: 
первый создает массив*/
MethodArrayOne(array);
ShowArray(array);
Console.WriteLine();
// второй: ищет наибольшее/наименьшее число
MethodArrayTwo(array);
Console.WriteLine();
Console.WriteLine("{0}", MethodArrayTwo(array));
// третий метод ищет сумму ?

double[] MethodArrayOne(double[] array) {
    Random rnd = new Random();
    double chislo = 0;
    for (int i = 0; i < 10; i++) {
        chislo = rnd.NextDouble();
        array[i] = rnd.Next();
        array[i] += chislo;
    }
    return array;
}

void ShowArray(double[] array) {
    for (int i = 0; i < array.Length; i++) {
        Console.WriteLine(array[i] + " ");
    }
}

double MethodArrayTwo(double[] array) {
    double min, max;
    min = max = 0;
    for (int i = 0; i < array.Length; i++) {
        if (array[i] > max) max = array[i];
        if (array[i] < min) min = array[i];
    }
    return max - min;
}