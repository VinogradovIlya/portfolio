Console.WriteLine("Задайте массив. Напишите программу, которая определяет, присутствует ли заданное число в массиве.");
Console.WriteLine();

/* два метода:
первый собирает массив*/
int[] array = new int[10];
MetodArrayOne();
ShowArray(array);
Console.WriteLine();
//второй ищет определенное число
Console.WriteLine();
Console.Write("введите искомое число: ");
int chislo = Convert.ToInt32(Console.ReadLine());
int count = 0;
MetodArrayTwo(array, chislo, count);

int[] MetodArrayOne() {
    for (int i = 0; i < array.Length; i++) {
        array[i] = new Random().Next(0, 1001);
    }
    return array;
}

void ShowArray(int[] array) {
    for (int i = 0; i < array.Length; i++) {
        Console.Write("{0} ", array[i]);
    }
}

void MetodArrayTwo(int[] array, int chislo, int count) {
    for (int i = 0; i < array.Length; i++) {
        if (chislo == array[i]) count += 1;
    }
    if (count > 0) Console.WriteLine("число присутсвует");
    else Console.WriteLine("число отсутсвует");
}