Console.WriteLine("Напишите программу замены элементов массива: положительные элементы замените на соответствующие отрицательные, и наоборот.");

Console.WriteLine("введите размер массива: ");
int size = Convert.ToInt32(Console.ReadLine());
int[] array = new int[size];
/* два метода:
первый собирает массив*/
MetodArrayOne(size);
// второй инвертирует значения
MetodArrayTwo(array, size);
ShowArray(array, size);

int[] MetodArrayOne(int size) {
    for (int i = 0; i < size; i++) {
        Console.Write($"введите {i + 1} элемент массива: ");
        array[i] = Convert.ToInt32(Console.ReadLine());
    }
    return array;
}

void ShowArray(int[] array, int size) {
    for (int i = 0; i < size; i++) {
        Console.Write("{0} ", array[i]);
    }
}

int[] MetodArrayTwo(int[] array, int size) {
    // int result = 0;
    for (int i = 0; i < size; i++) {
        array[i] *= -1;
    }
    return array;
}