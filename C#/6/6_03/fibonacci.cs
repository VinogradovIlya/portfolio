Console.WriteLine("Не используя рекурсию, выведите первые N чисел Фибоначчи. Первые два числа Фибоначчи: 0 и 1.");

Fibonacci(10, 0, 1);
Console.WriteLine();
ShowArray(
    MyFibonacci(10));

void Fibonacci(int size, int start, int next) {
    Console.Write($"{start} ");
       while (size > 1) {
        int temp = 0;
        temp = start;
        start += next;
        next = temp;
        Console.Write($"{start} ");
        size--;
    }
}

int[] MyFibonacci(int size) {
    int[] array = new int[size];
    array[0] = 0;
    array[1] = 1;
    for (int i = 2; i < size; i++) {
        array[i] = array[i - 1] + array[i - 2];
    }
    return array;
}

void ShowArray(int[] array) {
    for (int i = 0; i < array.Length; i++) {
        Console.Write("{0} ", array[i]);
    }
    Console.WriteLine();
}