Console.WriteLine("сортировка чисел в массиве");

// Console.WriteLine("введите сколько чисел хотите отсортировать: ");
// int razmer = Convert.ToInt32(Console.ReadLine());

int[] arr = {9, 8, 7, 6, 5, 4, 3, 2, 1};
PrintArray(arr);
MinSort(arr);
PrintArray(arr);

void PrintArray(int[] array) 
{
    int count = array.Length;
    for (int i = 0; i < count; i++)
    {
        Console.Write($"{array[i]} ");
    }
    Console.WriteLine();
}

void MinSort(int[] array) 
{
    for (int i = 0; i < array.Length - 1; i++)
    {
        int minPosition = i;
        for (int j = i + 1; j < array.Length; j++)
        {
            if(array[j] < array[minPosition]) {
                minPosition = j;
            }
        }
        int temporary = array[i];
        array[i] = array[minPosition];
        array[minPosition] = temporary;
    }
}
