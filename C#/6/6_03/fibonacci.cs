Console.WriteLine("Не используя рекурсию, выведите первые N чисел Фибоначчи. Первые два числа Фибоначчи: 0 и 1.");

Fibonacci(10, 0, 1);
Console.WriteLine();

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