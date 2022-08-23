Console.WriteLine("Напишите программу, которая задаёт массив из 8 элементов и выводит их на экран.");

// CreateArray();
// void CreateArray() {
    string[] array = new string[8];
    for (int i = 0; i < 8; i++) {
        Console.Write($"введите число {i + 1}: ");
        array[i] = Console.ReadLine();
    }
// }

ShowArray(array);
void ShowArray(string[] array) {
    for (int i = 0; i < array.Length; i++) {
        Console.Write(array[i] + " ");
    }
    Console.WriteLine();
}