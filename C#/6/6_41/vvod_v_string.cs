Console.WriteLine("Пользователь вводит с клавиатуры M чисел. Посчитайте, сколько чисел больше 0 ввёл пользователь.");

Console.WriteLine("введите числа: ");
string[] array = Console.ReadLine().Split(new Char[] { ' ' });

int Change(string[] array) {
    int count = 0;
    int number = 0;
    for (int i = 0; i < array.Length; i++) {
        number = Convert.ToInt32(array[i]);
        if (number > 0) count++;
    }
    return count;
}
Console.WriteLine("{0}", Change(array));