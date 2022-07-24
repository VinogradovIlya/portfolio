Console.WriteLine("Напишите программу, которая выводит случайное число из отрезка [10, 99] и показывает наибольшую цифру числа.");
int chislo = new Random().Next(10, 100);
Console.WriteLine("число: " + chislo);
int number1 = chislo / 10;
int number2 = chislo % 10;
if (number1 > number2) {
    Console.WriteLine($"наибольшая цифра: {number1}");
    } else {
        Console.WriteLine("наибольшая цифра: {0}", number2);
        }



// таким образом я могу взаимодействовать с цифрами из числа, как захочу



// int input() {
//     Console.WriteLine("Напишите программу, которая выводит случайное число из отрезка [10, 99] и показывает наибольшую цифру числа.");
//     int chislo = new Random().Next(10, 100);
//     Console.WriteLine("число: " + chislo);
//     return chislo;
// }

// void output(int chislo) {
//     int number1 = chislo / 10;
//     int number2 = chislo % 10;
//     if (number1 > number2) {
//     Console.Write($"наибольшая цифра: {number1}");
//     } else {
//         Console.Write("наибольшая цифра: {0}", number2);
//     }
// }

// int main() {
//     input();
//     output(chislo);
//     return 0;
// }