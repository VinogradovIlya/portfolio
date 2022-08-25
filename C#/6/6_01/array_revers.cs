Console.WriteLine("Напишите программу, которая перевернёт одномерный массив (последний элемент будет на первом месте, а первый - на последнем и т.д.)");

/* два метода:
первый собирает массив*/
int[] array = new int[10];
CreateArray();
ShowArray(array);
//второй переворачивает массив
InvertArray(array);
ShowArray(array);

int[] CreateArray() {
    for (int i = 0; i < array.Length; i++) {
        array[i] = new Random().Next(0, 1000);
    }
    return array;
}

void ShowArray(int[] array) {
    for (int i = 0; i < array.Length; i++) {
        Console.Write("{0} ", array[i]);
    }
    Console.WriteLine();
}

int[] InvertArray(int[] array) {
    for (int i = 0, j = array.Length - 1; i < j; i++, j--) {
        int temp = 0;
        temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
    return array;
}