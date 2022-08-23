Console.WriteLine("введите размер массива: ");
int size = Convert.ToInt32(Console.ReadLine());
int[] array = new int[size];

Console.WriteLine("введите нижний диапазон массива: ");
int min = Convert.ToInt32(Console.ReadLine());
Console.WriteLine("введите верхний диапазон массива: ");
int max = Convert.ToInt32(Console.ReadLine());

CreateRandomArray(size, min, max);
ShowArray(array);

int[] CreateRandomArray(int size, int min, int max) {
    for (int i = 0; i < size; i++) {
        array[i] = new Random().Next(min, max + 1);
    }
    return array;
}

Console.WriteLine("*************************************************");
//*********************************************************************


// Console.WriteLine("введите размер массива: ");
// int size = Convert.ToInt32(Console.ReadLine());
// int[] array = new int[size];

CreateArray(size);
ShowArray(array);

int[] CreateArray(int size){
    for (int i = 0; i < size; i++) {
        Console.WriteLine($"введите {i + 1} элемент: ");
        array[i] = Convert.ToInt32(Console.ReadLine());
    }
    return array;
}

Console.WriteLine("*************************************************");
//*********************************************************************


void ShowArray(int[] array) {
    for (int i = 0; i < array.Length; i++) {
        Console.Write(array[i] + " ");
    }
    Console.WriteLine();
}


Console.WriteLine("*************************************************");
//*********************************************************************