Console.WriteLine("Написать программу, принимающую на вход массив строк и генерирующую новый массив, состоящий из элементов, начинающихся на символ s1 и заканчивающихся на символ s2");

Console.Write("введите размер массива: ");
string[] CreateStringArray( number);

string[] CreateStringArray(int number) {
    string[] pupkaAlupka = new string[number];
    for (int i = 0; i < number; i++) {
        Console.Write($"введите {i+1} слово: ");
        pupkaAlupka[i] = Console.ReadLine();
    }
    return pupkaAlupka;
}


// int main() {
//     if () {
//         return a
//     }
//     return b
// }