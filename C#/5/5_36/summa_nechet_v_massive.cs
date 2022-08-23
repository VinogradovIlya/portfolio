Console.WriteLine("Задайте массив, заполненный случайными числами. Найдите сумму элементов, стоящих на нечётных позициях.");

int[] array = new int[10];

/* два метода: 
первый создает массив*/
MethodArrayOne(array);
ShowArray(array);
Console.WriteLine();
// второй: считает сумму
MethodArrayTwo(array);
Console.WriteLine("{0}", MethodArrayTwo(array));

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

int MethodArrayTwo(int[] array) {
    int sum = 0;
    for (int i = 0; i < array.Length; i++) {
        int count = i % 2;
        if (count == 0) {
            sum += array[i];
        }
    }
    return sum;
}